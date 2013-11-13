//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_port.hpp
 * @brief		iris unit test �ˑ��֐� �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_port_HPP_7893F685_A1A9_477a_82E8_BF06237697FF_
#define INCG_IRIS_iutest_port_HPP_7893F685_A1A9_477a_82E8_BF06237697FF_

//======================================================================
// include
#if defined(__MWERKS__)
#  define _MSL_USING_NAMESPACE
#endif

#include "iutest_internal_defs.hpp"

#if defined(IUTEST_OS_LINUX) || defined(IUTEST_OS_CYGWIN)
#  include <unistd.h>
#  include <locale.h>
#endif

namespace iutest {

#ifdef IUTEST_OS_NACL
namespace nacl
{

/**
 * @brief	printf
*/
void	vprint_message(const char *fmt, va_list va);
void	print_message(const char *fmt, ...);

}
#endif

namespace internal {
namespace posix
{

const char* GetEnv(const char* name);
int PutEnv(const char* expr);

const char* GetCWD(char* buf, size_t length);
::std::string GetCWD(void);

void SleepMillisec(unsigned int millisec);

#if defined(IUTEST_OS_WINDOWS_MOBILE)
void Abort(void);
#else
inline void Abort(void) { abort(); }
#endif

}	// end of namespace posix

inline void SleepMilliseconds(int n)	{ posix::SleepMillisec(static_cast<unsigned int>(n)); }

}	// end of namespace internal

namespace detail
{

namespace posix = internal::posix;

/**
 * @brief	���ϐ��̐ݒ�
*/
bool SetEnvironmentVariable(const char* name, const char* value);


/**
 * @brief	���ϐ��̎擾
 * @param [in]	name	= ���ϐ���
 * @param [out]	buf		= �o�̓o�b�t�@
 * @return	����
*/
bool GetEnvironmentVariable(const char* name, char* buf, size_t size);

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<size_t SIZE>
inline bool GetEnvironmentVariable(const char* name, char (&buf)[SIZE])
{
	return GetEnvironmentVariable(name, buf, SIZE);
}

#endif

/**
 * @brief	���ϐ��̎擾
 * @param [in]	name	= ���ϐ���
 * @param [out]	var		= �o�͕�����
 * @return	����
*/
bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentVariable(const char* name, ::std::string& var);

/**
 * @brief	���ϐ��̎擾
 * @param [in]	name	= ���ϐ���
 * @param [out]	var		= �o�͐��l
 * @return	����
*/
bool IUTEST_ATTRIBUTE_UNUSED_ GetEnvironmentInt(const char* name, int& var);

#if defined(IUTEST_OS_WINDOWS)
namespace win
{

/**
 * @brief	������ϊ�
*/
::std::string IUTEST_ATTRIBUTE_UNUSED_ WideStringToMultiByteString(const wchar_t* wide_c_str);

/**
 * @brief	HRESULT �̃G���[��������擾
 * @param [in]	hr	= �G���[�l
 * @return	������
*/
::std::string IUTEST_ATTRIBUTE_UNUSED_ GetHResultString(HRESULT hr);

}	// end of namespace win
#endif

/**
 * @brief	���O
*/
class IUTestLog
{
public:
	enum Level
	{
		LOG_INFO
		, LOG_WARNING
		, LOG_ERROR
		, LOG_FATAL
	};
public:
	IUTestLog(Level level, const char* file, int line);

	~IUTestLog(void);

public:
	iuStringStream::type& GetStream(void) { return m_stream; }
private:
	const Level kLevel;
	iuStringStream::type m_stream;

	IUTEST_PP_DISALLOW_COPY_AND_ASSIGN(IUTestLog);
};

#define IUTEST_LOG_(level)	::iutest::detail::IUTestLog(::iutest::detail::IUTestLog::LOG_##level, __FILE__, __LINE__).GetStream()
#define IUTEST_CHECK_(condition)	\
	IUTEST_AMBIGUOUS_ELSE_BLOCKER_	\
	if( ::iutest::detail::IsTrue(condition) )	\
		;										\
	else										\
		IUTEST_LOG_(FATAL) << "Condition " #condition " failed. "


}	// end of namespace detail
}	// end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_port.ipp"
#endif

#endif