#include <windows.h>
#include <iostream>
#include "lab3.h"

using namespace std;

#define THREADCOUNT 13

DWORD ThreadID;
HANDLE iThread[THREADCOUNT];
HANDLE semE, semM, semN;
HANDLE stop, go;
HANDLE iMutex;

unsigned int lab3_thread_graph_id()
{
    return 15;
}

const char* lab3_unsynchronized_threads()
{
    return "bcdgh";
}

const char* lab3_sequential_threads()
{
    return "emn";
}

DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_i(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_m(LPVOID);
DWORD WINAPI thread_n(LPVOID);
DWORD WINAPI thread_p(LPVOID);

int lab3_init()
{

    iMutex = CreateMutex(NULL, 0, NULL);
    if (iMutex == NULL) {
        cout << "CreateMutex error: " << GetLastError();
        return 1;
    }

    semE = CreateSemaphore(NULL, 1, 1, NULL);
    if (semE == NULL)
    {
        std::cout << "CreateSemaphore error: " << GetLastError();
        return 1;
    }
    semM = CreateSemaphore(NULL, 0, 1, NULL);
    if (semM == NULL)
    {
        std::cout << "CreateSemaphore error: " << GetLastError();
        return 1;
    }
    semN = CreateSemaphore(NULL, 0, 1, NULL);
    if (semN == NULL)
    {
        std::cout << "CreateSemaphore error: " << GetLastError();
        return 1;
    }

    stop = CreateSemaphore(NULL, 0, 2, NULL);
    if (stop == NULL)
    {
        std::cout << "CreateSemaphore error: " << GetLastError();
        return 1;
    }

    go = CreateSemaphore(NULL, 0, 2, NULL);
    if (go == NULL)
    {
        std::cout << "CreateSemaphore error: " << GetLastError();
        return 1;
    }

    iThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (iThread[3] == NULL) {
        return GetLastError();
    }

    /// wait-d
    WaitForSingleObject(iThread[3], INFINITE);
    /// close-d
    CloseHandle(iThread[3]);
    CloseHandle(stop);
    CloseHandle(go);
    CloseHandle(iMutex);
    /// close-semE, semM, semN
    CloseHandle(semE);
    CloseHandle(semM);
    CloseHandle(semN);



    return 0;
}


DWORD WINAPI thread_d(LPVOID lpParam) {
    /// 1-interval ///
    /// start-a
    iThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (iThread[0] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    // wait-a
    WaitForSingleObject(iThread[0], INFINITE);

    /// 2-interval ///
    // start-h
    iThread[3] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (iThread[3] == NULL) {
        return GetLastError();
    }
    // start-g
    iThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (iThread[6] == NULL) {
        return GetLastError();
    }
    // start-b
    iThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (iThread[1] == NULL) {
        return GetLastError();
    }
    // start-c
    iThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (iThread[2] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    // stop-h
    WaitForSingleObject(stop, INFINITE); 
    // wait-g
    WaitForSingleObject(iThread[6], INFINITE);
    // wait-b
    WaitForSingleObject(iThread[1], INFINITE);
    // wait-c
    WaitForSingleObject(iThread[2], INFINITE);

    // 3-interval //

    // go-h
    ReleaseSemaphore(go, 1, NULL); 

    // start-k
    iThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (iThread[9] == NULL) {
        return GetLastError();
    }

    // start-i
    iThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (iThread[8] == NULL) {
        return GetLastError();
    }

    // start-f
    iThread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (iThread[5] == NULL) {
        return GetLastError();
    }

    // start-e
    iThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (iThread[4] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "d" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    // stop-e
    WaitForSingleObject(stop, INFINITE);
    // wait-h
    WaitForSingleObject(iThread[7], INFINITE);
    // wait-k
    WaitForSingleObject(iThread[9], INFINITE);
    // wait-i
    WaitForSingleObject(iThread[8], INFINITE);
    // wait-f
    WaitForSingleObject(iThread[5], INFINITE);

    // start-n
    iThread[11] = CreateThread(NULL, 0, thread_n, NULL, 0, &ThreadID);
    if (iThread[11] == NULL) {
        return GetLastError();
    }

    // wait-n
    WaitForSingleObject(iThread[11], INFINITE);
    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam) {
    // 4-interval //
    // go-e
    ReleaseSemaphore(go, 1, NULL);
    // start-m
    iThread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (iThread[10] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(semN, INFINITE);
        WaitForSingleObject(iMutex, INFINITE);
        cout << "n" << flush;
        computation();
        ReleaseMutex(iMutex);
        ReleaseSemaphore(semE, 1, NULL);
    }

    // wait-e
    WaitForSingleObject(iThread[4], INFINITE);
    // wait-m
    WaitForSingleObject(iThread[10], INFINITE);

    // 5-interval //
    // start-p
    iThread[12] = CreateThread(NULL, 0, thread_p, NULL, 0, &ThreadID);
    if (iThread[12] == NULL) {
        return GetLastError();
    }

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "n" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    // wait-p
    WaitForSingleObject(iThread[12], INFINITE);
    return 0;
}

DWORD WINAPI thread_a(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "a" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "b" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "c" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    ReleaseSemaphore(stop, 1, NULL);
    WaitForSingleObject(go, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(semE, INFINITE);
        WaitForSingleObject(iMutex, INFINITE);
        cout << "e" << flush;
        computation();
        ReleaseMutex(iMutex);
        ReleaseSemaphore(semM, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "g" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "f" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    ReleaseSemaphore(stop, 1, NULL);
    WaitForSingleObject(go, INFINITE);

    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "h" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "i" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "k" << flush;
        computation();
        ReleaseMutex(iMutex);
    }
    return 0;
}

DWORD WINAPI thread_p(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(iMutex, INFINITE);
        cout << "p" << flush;
        computation();
        ReleaseMutex(iMutex);
    }

    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam) {
    for (int i = 0; i < 3; i++) {
        WaitForSingleObject(semM, INFINITE);
        WaitForSingleObject(iMutex, INFINITE);
        cout << "m" << flush;
        computation();
        ReleaseMutex(iMutex);
        ReleaseSemaphore(semN, 1, NULL);
    }
    return 0;
}
