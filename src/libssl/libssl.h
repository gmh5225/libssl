/*
�ļ�����ȡ��VS2017�Ŀ���̨ʾ�����̵�ͷ�ļ�.

����:Ԥ����ͷ,����û��������ǿ�Ƶ�һ����������ļ�.

ע��:
1.����ļ�ֻ����ϵͳ��ͷ�ļ���һЩ����������.
2.����ļ�ֻ����һЩ����������.
3.Ҳ����˵���ͷ�ļ�ֻ׼��������ļ�,��׼�ٰ������ϵͳ�ļ�.

���ļ���Ҫ���ڽ��:
1.ϵͳ�ļ��������µı����������.
2.ͳһ�滮�ļ��İ�����ϵ.
*/


#pragma once


#if (NTDDI_VERSION >= NTDDI_VISTA)
#define NDIS60 1
#define NDIS_SUPPORT_NDIS6 1
#endif 

#define POOL_NX_OPTIN 1
#define _CRT_NON_CONFORMING_SWPRINTFS
#define INITGUID
#define NTSTRSAFE_LIB

#pragma warning(disable:4200) // ʹ���˷Ǳ�׼��չ : �ṹ/�����е����С����
#pragma warning(disable:4201) // unnamed struct/union
#pragma warning(disable:4214) // ʹ���˷Ǳ�׼��չ: ���������λ������
#pragma warning(disable:4127) // �������ʽ�ǳ���
#pragma warning(disable:4057) // ����΢��ͬ�Ļ����ͼ��Ѱַ�ϲ�ͬ
#pragma warning(disable:4152) // �Ǳ�׼��չ�����ʽ�еĺ���/����ָ��ת��
#pragma warning(disable:28172) //The function 'XXX' has PAGED_CODE or PAGED_CODE_LOCKED but is not declared to be in a paged segment. ԭ��1.������IRQL������2.�����ڵĺ����Ĳ����þֲ���������Ҫ����������ǷǷ�ҳ�ڴ档

#include <winerror.h>
#include <ntifs.h>
#include <wdm.h>
#include <ntddk.h>
#include <windef.h> //Ӧ�÷���ntddk.h�ĺ���.
#include <in6addr.h>
#include <ip2string.h>
#include <guiddef.h>
#include <ndis.h>
#include <initguid.h> //��̬����UUID�õģ�����error LNK2001��
#include <Ntstrsafe.h>
#include <ipmib.h>
#include <netpnp.h>
#include <ntintsafe.h>
#include <fltkernel.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <Bcrypt.h>

/*
WDK7600.16385.1���ں�ͷ�ļ�û��u_short�Ķ���,�û����ͷ�ļ���u_short�Ķ���.
SOCKADDR�ṹ���õ�u_short.
SOCKADDR��ws2def.h�ж���.
ws2def.h������ֱ�Ӱ���.
netioapi.h����ws2def.h���ļ�.
������WDK7600.16385.1��,���������Ӧ�ò��ͷ�ļ�,Ӧ���ڰ���netioapi.h֮ǰ,����u_short�Ķ���.
����,ÿ������(������Ӱ���)ws2def.h��c/cpp�ļ�������һ��ѵĴ���.
*/
typedef unsigned short  u_short;
#include <netioapi.h>
//#include <ws2def.h>
#include <ws2ipdef.h>
#include <mstcpip.h>
#include <wmilib.h>
#include <wmistr.h>
#include <tdi.h>
#include <tdiinfo.h>
#include <tdikrnl.h>
#include <tdistat.h>
#include <fwpmk.h>
#include <wsk.h>
#include <ntimage.h>
#include <fwpsk.h>  //NDIS61
#include <dontuse.h>
#include <suppress.h>
#include <aux_klib.h>
#include <assert.h>
#include <Ntdddisk.h>
#include <intrin.h> //VS2012���롣
#include <immintrin.h>//VS2012���롣
//#include <mmintrin.h> //WDK ���롣
//#include <emmintrin.h>//WDK ���롣
//#include <xmmintrin.h>//WDK ���롣
#include <wdmsec.h>
#define SECURITY_KERNEL
#include <sspi.h>


#define TAG 'tset' //test


//////////////////////////////////////////////////////////////////////////////////////////////////


#define _Outptr_allocatesMem_ _Outptr_result_nullonfailure_ __drv_allocatesMem(Mem)
#define _Out_allocatesMem_ _Out_ __drv_allocatesMem(Mem)
#define _Out_allocatesMem_size_(size) _Out_allocatesMem_ _Post_writable_byte_size_(size)
#define _FreesMem_ _Pre_notnull_ _Post_ptr_invalid_ __drv_freesMem(Mem)
#define _In_freesMem_ _In_ _FreesMem_
#define _In_aliasesMem_ _In_ _Pre_notnull_ _Post_ptr_invalid_ __drv_aliasesMem
#define _Return_allocatesMem_ __drv_allocatesMem(Mem) _Post_maybenull_ _Must_inspect_result_
#define _Return_allocatesMem_size_(size) _Return_allocatesMem_ _Post_writable_byte_size_(size)


//////////////////////////////////////////////////////////////////////////////////////////////////


typedef PVOID KPH_SOCKET_HANDLE;
typedef PVOID * PKPH_SOCKET_HANDLE;

typedef PVOID KPH_TLS_HANDLE;
typedef PVOID * PKPH_TLS_HANDLE;


//////////////////////////////////////////////////////////////////////////////////////////////////


EXTERN_C_START


//////////////////////////////////////////////////////////////////////////////////////////////////


_IRQL_requires_max_(DISPATCH_LEVEL)
VOID KphSocketClose(KPH_SOCKET_HANDLE Socket);

_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketConnect(
    _In_ USHORT SocketType,
    _In_ ULONG Protocol,
    _In_ PSOCKADDR LocalAddress,
    _In_ PSOCKADDR RemoteAddress,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Outptr_allocatesMem_ PKPH_SOCKET_HANDLE Socket
);

_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketSend(
    _In_ KPH_SOCKET_HANDLE Socket,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
);

_IRQL_requires_max_(DISPATCH_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketRecv(
    _In_ KPH_SOCKET_HANDLE Socket,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Out_writes_bytes_to_(*Length, *Length) PVOID Buffer,
    _Inout_ PULONG Length
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphInitializeSocket(VOID);

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphCleanupSocket(VOID);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphGetAddressInfo(
    _In_ PUNICODE_STRING NodeName,
    _In_opt_ PUNICODE_STRING ServiceName,
    _In_opt_ PADDRINFOEXW Hints,
    _In_opt_ PLARGE_INTEGER Timeout,
    _Outptr_allocatesMem_ PADDRINFOEXW * AddressInfo
);

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphFreeAddressInfo(_In_freesMem_ PADDRINFOEXW AddressInfo);


//////////////////////////////////////////////////////////////////////////////////////////////////


_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketTlsCreate(_Outptr_allocatesMem_ PKPH_TLS_HANDLE Tls);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketTlsHandshake(
    _In_ KPH_SOCKET_HANDLE Socket,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ KPH_TLS_HANDLE Tls,
    _In_ PUNICODE_STRING TargetName
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketTlsSend(
    _In_ KPH_SOCKET_HANDLE Socket,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ KPH_TLS_HANDLE Tls,
    _In_reads_bytes_(Length) PVOID Buffer,
    _In_ ULONG Length
);

_IRQL_requires_max_(PASSIVE_LEVEL)
_Must_inspect_result_
NTSTATUS KphSocketTlsRecv(
    _In_ KPH_SOCKET_HANDLE Socket,
    _In_opt_ PLARGE_INTEGER Timeout,
    _In_ KPH_TLS_HANDLE Tls,
    _Out_writes_bytes_to_(*Length, *Length) PVOID Buffer,
    _Inout_ PULONG Length
);

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphSocketTlsShutdown(_In_ KPH_SOCKET_HANDLE Socket, _In_ KPH_TLS_HANDLE Tls);

_IRQL_requires_max_(PASSIVE_LEVEL)
VOID KphSocketTlsClose(_In_freesMem_ KPH_TLS_HANDLE Tls);


//////////////////////////////////////////////////////////////////////////////////////////////////


EXTERN_C_END
