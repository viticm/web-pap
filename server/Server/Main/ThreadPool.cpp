#include "stdafx.h"


#include "ThreadPool.h"

ThreadPool::ThreadPool( )
{
__ENTER_FUNCTION

    for( INT i=0; i<MAX_THREAD; i++ )
    {
        m_pThread[i] = NULL ;
    }
    m_Count = 0 ;
    m_Position = 0 ;
    m_ThreadCount = 0;

__LEAVE_FUNCTION
}

ThreadPool::~ThreadPool( )
{
__ENTER_FUNCTION

    for( INT i=0; i<MAX_THREAD; i++ )
    {
        SAFE_DELETE( m_pThread[i] ) ;
    }
    m_Count = 0 ;
    m_Position = 0 ;

__LEAVE_FUNCTION
}

Thread** ThreadPool::GetThread()
{
__ENTER_FUNCTION
    return m_pThread;
__LEAVE_FUNCTION
}

BOOL ThreadPool::AddThread( UINT uThreadIndex, Thread* pThread )
{
__ENTER_FUNCTION

    //for( INT i=0; i<MAX_THREAD; i++ )
    //{
    //if( NULL == m_pThread[ uThreadIndex ] )
    //{
    m_pThread[ uThreadIndex ] = pThread ;
    m_Position++ ;
    Assert( uThreadIndex<=MAX_THREAD ) ;
    //m_Count++ ;
    m_ThreadCount++ ;
    Assert( m_ThreadCount<=MAX_THREAD ) ;
    return TRUE ;
    //}

    //m_Position++ ;
    //Assert( m_Position<=MAX_THREAD ) ;
    //}

__LEAVE_FUNCTION

    return FALSE ;
}

BOOL ThreadPool::DelThread( TID id )
{
__ENTER_FUNCTION

    for( INT i=0; i<MAX_THREAD; i++ )
    {
        if( m_pThread[i] && m_pThread[i]->getTID()==id )
        {
            m_Position = i ;
            m_pThread[i] = NULL ;
            m_ThreadCount -- ;
            Assert( m_ThreadCount >= 0 ) ;

            return TRUE ;
        }

    }

__LEAVE_FUNCTION

    return FALSE ;
}

Thread* ThreadPool::GetThread( TID id )
{
__ENTER_FUNCTION

    for( INT i=0; i<MAX_THREAD; i++ )
    {
        if( m_pThread[i] && m_pThread[i]->getTID()==id )
        {
            return m_pThread[i] ;
        }
    }

__LEAVE_FUNCTION


    return NULL ;
}

Thread* ThreadPool::GetThreadByIndex( UINT index )
{
__ENTER_FUNCTION

    if( index>= m_ThreadCount )
        return NULL ;

    return m_pThread[index] ; 

__LEAVE_FUNCTION

    return NULL ;
}

BOOL ThreadPool::Start( )
{
__ENTER_FUNCTION

    for( INT i=0; i < m_ThreadCount; i++ )
    {
        if( m_pThread[ i ] )
        {
            m_pThread[ i ]->start() ;
        }
    }


    return TRUE ;

__LEAVE_FUNCTION

    return FALSE ;
}

BOOL ThreadPool::Stop( )
{
__ENTER_FUNCTION

    for( INT i=0; i < m_ThreadCount; i++ )
    {
        if( m_pThread[i] )
            m_pThread[i]->stop() ;
    }

    return TRUE ;

__LEAVE_FUNCTION

    return FALSE ;
}
