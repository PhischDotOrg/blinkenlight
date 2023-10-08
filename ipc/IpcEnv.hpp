/*-
 * $Copyright$
-*/

#ifndef _IPCENV_HPP_56fe3a23_7f69_4f43_aa9a_634c7b5d75c2
#define _IPCENV_HPP_56fe3a23_7f69_4f43_aa9a_634c7b5d75c2

namespace ipc {

/*******************************************************************************
 * 
 ******************************************************************************/
#if !defined(IPC_ENV)
#define IPC_ENV Undefined
#endif

/*******************************************************************************
 * 
 ******************************************************************************/
typedef enum IpcEnv_e {
    Undefined,
    Posix,
    FreeRTOS
} IpcEnv_t;

} /* namespace ipc */

#endif /* _IPCENV_HPP_56fe3a23_7f69_4f43_aa9a_634c7b5d75c2 */
