//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_console.hpp
 * @brief		iris unit test console �t�@�C��
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
#ifndef INCG_IRIS_iutest_console_HPP_DCAC5025_B7BB_424e_A849_9E6FE0A3B460_
#define INCG_IRIS_iutest_console_HPP_DCAC5025_B7BB_424e_A849_9E6FE0A3B460_

//======================================================================
// include
#include <stdio.h>
#include <stdarg.h>

namespace iutest {
namespace detail
{

//======================================================================
// define
#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)	vprintf(f, a)
#endif

#ifndef IUTEST_HAS_COLORCONSOLE
#  if defined(IUTEST_OS_WINDOWS_MOBILE) || defined(IUTEST_OS_NACL)
#    define IUTEST_HAS_COLORCONSOLE	0	//!< �F���^�[�~�i�����g�p�\���ǂ���
#  else
#    define IUTEST_HAS_COLORCONSOLE	1	//!< �F���^�[�~�i�����g�p�\���ǂ���
#  endif
#endif

//======================================================================
// class
/**
 * @internal
 * @brief	�J�X�^�� Logger �N���X
*/
class iuLogger
{
public:
	virtual void output(const char* fmt, ...)
	{
		va_list va;
		va_start(va, fmt);
		voutput(fmt, va);
		va_end(va);
	}
	virtual void voutput(const char* fmt, va_list va) = 0;
};

/**
 * @internal
 * @brief	�R���\�[���N���X
*/
class iuConsole
{
	template<typename T>
	struct Variable
	{
		static iuLogger*	m_pLogger;
	};

	typedef Variable<void>	var;

public:
	//! �R���\�[�������F
	enum Color
	{
		black,
		red,
		green,
		yellow,
		blue,
		magenta,
		cyan,
		white
	};
public:
	/**
	 * @brief	�W���o��
	*/
	static inline void output(const char *fmt, ...);

	/**
	 * @brief	�W���o��
	 * @note	logger ��ʂ��Ȃ�
	*/
	static inline void voutput(const char* fmt, va_list va);

	/**
	 * @brief	�F�w��ŕW���o��
	 * @param [in]	color	= �����F
	*/
	static inline void	color_output(Color color, const char *fmt, ...);

public:
	//! Logger �̃Z�b�g
	static iuLogger*	SetLogger(iuLogger* logger)
	{
		iuLogger* pre = var::m_pLogger;
		var::m_pLogger = logger;
		return pre;
	}
private:
	static inline void color_output_impl(Color color, const char* fmt, va_list va);
	static inline void voutput_impl(const char* fmt, va_list va);
	static inline bool IsShouldUseColor(bool use_color);

private:
	static inline bool IsStringEqual(const char* str1, const char* str2) { return strcmp(str1, str2) == 0; }

	static bool	IsColorModeOff(void)
	{
#if	defined(INCG_IRIS_iutest_HPP_) && !defined(IUTEST_USE_GTEST)
		return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_OFF);
#else
		return IUTEST_FLAG(color) == "no";
#endif
	}
	static bool	IsColorModeOn(void)
	{
#if	defined(INCG_IRIS_iutest_HPP_) && !defined(IUTEST_USE_GTEST)
		return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ON);
#else
		return IUTEST_FLAG(color) == "yes";
#endif
	}
	static bool IsColorModeAnsi(void)
	{
#if	defined(INCG_IRIS_iutest_HPP_) && !defined(IUTEST_USE_GTEST)
		return TestFlag::IsEnableFlag(TestFlag::CONSOLE_COLOR_ANSI);
#else
		return false;
#endif
	}
};

inline void	iuConsole::output(const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);
	voutput_impl(fmt, va);
	va_end(va);
}
inline void	iuConsole::color_output(Color color, const char *fmt, ...)
{
	va_list va;
	va_start(va, fmt);

	if( IsShouldUseColor(true) )
	{
		color_output_impl(color, fmt, va);
	}
	else
	{
		voutput_impl(fmt, va);
	}

	va_end(va);
}

inline void iuConsole::voutput(const char* fmt, va_list va)
{
	IUTEST_VPRINTF(fmt, va);
}

inline void iuConsole::color_output_impl(Color color, const char* fmt, va_list va)
{
	(void)(fmt);
	(void)(va);
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MOBILE)
	if( !IsColorModeAnsi() )
	{
		const WORD attr[] = {
			0,
			FOREGROUND_RED,
			FOREGROUND_GREEN,
			FOREGROUND_GREEN | FOREGROUND_RED,
			FOREGROUND_BLUE,
			FOREGROUND_RED | FOREGROUND_BLUE,
			FOREGROUND_GREEN | FOREGROUND_BLUE,
			FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
		};
		const HANDLE stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		::GetConsoleScreenBufferInfo(stdout_handle, &csbi);
		const WORD wAttributes = csbi.wAttributes;

		fflush(stdout);
		::SetConsoleTextAttribute(stdout_handle, attr[color] | FOREGROUND_INTENSITY);

		voutput_impl(fmt, va);

		fflush(stdout);
		::SetConsoleTextAttribute(stdout_handle, wAttributes);
	}
	else
#endif
	{
		output("\033[1;3%cm", '0' + color);
		voutput_impl(fmt, va);
		output("\033[m");
	}
}

inline void iuConsole::voutput_impl(const char* fmt, va_list va)
{
	if( var::m_pLogger != NULL )
	{
		var::m_pLogger->voutput(fmt, va);
	}
	else
	{
		voutput(fmt, va);
	}
}

inline bool	iuConsole::IsShouldUseColor(bool use_color)
{
	if( IsColorModeOn() )
	{
		return true;
	}
	else if( IsColorModeOff() )
	{
		return false;
	}

#if !IUTEST_HAS_COLORCONSOLE
	(void)(use_color);
	return false;
#else
#if defined(IUTEST_OS_WINDOWS)
	return use_color;
#else
	const char* env = internal::posix::GetEnv("TERM");
	bool term_conf = (env != NULL) && (
		IsStringEqual(env, "xterm")
		|| IsStringEqual(env, "xterm-color")
		|| IsStringEqual(env, "xterm-256color")
		|| IsStringEqual(env, "screen")
		|| IsStringEqual(env, "screen-256color")
		|| IsStringEqual(env, "linux")
		|| IsStringEqual(env, "cygwin")
		);
	return use_color && term_conf;
#endif

#endif
}

}	// end of namespace detail
}	// end of namespace iutest

template<typename T>
::iutest::detail::iuLogger*	::iutest::detail::iuConsole::Variable<T>::m_pLogger = NULL;

#endif