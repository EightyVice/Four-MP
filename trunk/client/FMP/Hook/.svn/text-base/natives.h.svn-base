#pragma once

#include "types.h"
#include "../../../Shared/logging/log.h"
#include "natives_list.h"

int GetNativeAddressByHash(unsigned int a1);

///////////////////////////////////

class scrNativeCallContext
{
protected:
	typedef struct { float X, Y, Z; } Vector3;
	typedef struct { float X, Y, Z, W; } Vector4;

	ptr m_pReturn;
	unsigned int m_nArgCount;
	ptr m_pArgs;
        
	unsigned int m_nDataCount;
	Vector3 *m_pOriginalData[4];
	Vector4 m_TemporaryData[4];
};

class NativeContext :
    public scrNativeCallContext
{
private:
    enum
    {
        MaxNativeParams = 16,
        ArgSize = sizeof(unsigned int),
    };
    
    bool m_TempStack[MaxNativeParams * ArgSize];

public:
    __forceinline NativeContext()
    {
        m_pArgs = &m_TempStack;
        m_pReturn = &m_TempStack; 
        m_nArgCount = 0;
        m_nDataCount = 0;
    }

    template <typename T>
    __forceinline void Push(T value)
    {
        if (sizeof(T) > ArgSize)
        {
            throw "Argument has an invalid size";
        }
        else if (sizeof(T) < ArgSize)
        {
            *ptr_cast<unsigned int>(m_TempStack + ArgSize * m_nArgCount) = 0;
        }

        *ptr_cast<T>(m_TempStack + ArgSize * m_nArgCount) = value;
        m_nArgCount++;
    }

    template <typename T>
    __forceinline T GetResult()
    {
        while(m_nDataCount > 0)
        {
            m_nDataCount--;
            Vector3 *pVec3 = m_pOriginalData[m_nDataCount];
            Vector4 *pVec4 = &m_TemporaryData[m_nDataCount];
            pVec3->X = pVec4->X;
            pVec3->Y = pVec4->Y;
            pVec3->Z = pVec4->Z;
        }

        return *ptr_cast<T>(m_TempStack);
    }
};

class NativeInvoke
{
private:
	typedef void (_cdecl *NativeCall)(scrNativeCallContext *cxt);

	static inline void Invoke(NativeContext *cxt, unsigned int hash)
    {
		//Log::Debug("# Invoking native: 0x%x", hash);
		
        ptr fn = (ptr)GetNativeAddressByHash(hash);

		//Log::Debug("# Native address: 0x%x",fn);
		
        if(fn != 0)
        {
            NativeCall call = (NativeCall)fn;
            call(cxt);
        }

		//Log::Debug("# Call native complete");
    }
public:
	template <unsigned int Hash, typename R>
	static inline R Invoke()
	{
		NativeContext cxt;

		Invoke(&cxt, Hash);
		return cxt.GetResult<R>();
	}

	template <unsigned int Hash, typename R, typename T1>
    static inline R Invoke(T1 p1)
    {
        NativeContext cxt;

        cxt.Push(p1);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2>
    static inline R Invoke(T1 p1, T2 p2)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3>
    static inline R Invoke(T1 p1, T2 p2, T3 p3)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11, T12 p12)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);
        cxt.Push(p12);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12, typename T13>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11, T12 p12, T13 p13)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);
        cxt.Push(p12);
        cxt.Push(p13);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);
        cxt.Push(p12);
        cxt.Push(p13);
        cxt.Push(p14);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }

    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);
        cxt.Push(p12);
        cxt.Push(p13);
        cxt.Push(p14);
        cxt.Push(p15);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }


    template <unsigned int Hash, typename R, typename T1, typename T2, typename T3, typename T4,
                typename T5, typename T6, typename T7, typename T8, typename T9,
                typename T10, typename T11, typename T12, typename T13, typename T14,
                typename T15, typename T16>
    static inline R Invoke(T1 p1, T2 p2, T3 p3, T4 p4, T5 p5, T6 p6, T7 p7, T8 p8,
                        T9 p9, T10 p10, T11 p11, T12 p12, T13 p13, T14 p14, T15 p15, T16 p16)
    {
        NativeContext cxt;

        cxt.Push(p1);
        cxt.Push(p2);
        cxt.Push(p3);
        cxt.Push(p4);
        cxt.Push(p5);
        cxt.Push(p6);
        cxt.Push(p7);
        cxt.Push(p8);
        cxt.Push(p9);
        cxt.Push(p10);
        cxt.Push(p11);
        cxt.Push(p12);
        cxt.Push(p13);
        cxt.Push(p14);
        cxt.Push(p15);
        cxt.Push(p16);

        Invoke(&cxt, Hash);
        return cxt.GetResult<R>();
    }
};

//////////////////////////////////////////