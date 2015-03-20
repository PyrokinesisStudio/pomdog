﻿//
//  Copyright (C) 2013-2015 mogemimi.
//  Distributed under the MIT License. See LICENSE.md or
//  http://enginetrouble.net/pomdog/license for details.
//

#include "ConstantBufferGL4.hpp"
#include "ErrorChecker.hpp"
#include "TypesafeHelperGL4.hpp"
#include "../Utility/ScopeGuard.hpp"
#include "Pomdog/Utility/Assert.hpp"
#include <utility>

namespace Pomdog {
namespace Detail {
namespace RenderSystem {
namespace GL4 {
//-----------------------------------------------------------------------
template<>
struct TypesafeHelperGL4::OpenGLGetTraits<ConstantBufferObjectGL4> {
	constexpr static GLenum bufferObjectBinding = GL_UNIFORM_BUFFER_BINDING;
	constexpr static GLenum bufferObjectTarget = GL_UNIFORM_BUFFER;
};
//-----------------------------------------------------------------------
ConstantBufferGL4::ConstantBufferGL4(std::uint32_t byteWidth)
{
	// Generate constant buffer
	bufferObject = ([] {
		ConstantBufferObjectGL4 constantBuffer;
		glGenBuffers(1, constantBuffer.Data());
		return std::move(constantBuffer);
	})();

	auto const oldBufferObject = TypesafeHelperGL4::Get<ConstantBufferObjectGL4>();
	ScopeGuard scope([&oldBufferObject] {
		TypesafeHelperGL4::BindBuffer(oldBufferObject);
	});

	POMDOG_ASSERT(bufferObject);
	TypesafeHelperGL4::BindBuffer(*bufferObject);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindBuffer", __FILE__, __LINE__);
	#endif

	glBufferData(GL_UNIFORM_BUFFER, byteWidth, nullptr, GL_DYNAMIC_DRAW);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBufferData", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
ConstantBufferGL4::~ConstantBufferGL4()
{
	if (bufferObject) {
		glDeleteBuffers(1, bufferObject->Data());
	}
}
//-----------------------------------------------------------------------
void ConstantBufferGL4::GetData(std::uint32_t byteWidth, void* result) const
{
	POMDOG_ASSERT(result != nullptr);
	POMDOG_ASSERT(byteWidth > 0);

	auto const oldBufferObject = TypesafeHelperGL4::Get<ConstantBufferObjectGL4>();
	ScopeGuard scope([&oldBufferObject] {
		TypesafeHelperGL4::BindBuffer(oldBufferObject);
	});

	POMDOG_ASSERT(bufferObject);
	TypesafeHelperGL4::BindBuffer(*bufferObject);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindBuffer", __FILE__, __LINE__);
	#endif

	#if defined(DEBUG) && !defined(NDEBUG)
	{
		GLint bufferSize = 0;
		glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &bufferSize);
		POMDOG_ASSERT(byteWidth <= static_cast<std::size_t>(bufferSize));
	}
	#endif

	glGetBufferSubData(GL_UNIFORM_BUFFER, 0, byteWidth, result);

	#ifdef DEBUG
	ErrorChecker::CheckError("glGetBufferSubData", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
void ConstantBufferGL4::SetData(std::uint32_t offsetInBytes,
	void const* source, std::uint32_t sizeInBytes)
{
	POMDOG_ASSERT(source != nullptr);

	auto const oldBufferObject = TypesafeHelperGL4::Get<ConstantBufferObjectGL4>();
	ScopeGuard scope([&oldBufferObject] {
		TypesafeHelperGL4::BindBuffer(oldBufferObject);
	});

	POMDOG_ASSERT(bufferObject);
	TypesafeHelperGL4::BindBuffer(*bufferObject);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBindBuffer", __FILE__, __LINE__);
	#endif

	#if defined(DEBUG) && !defined(NDEBUG)
	{
		GLint bufferSize = 0;
		glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &bufferSize);
		POMDOG_ASSERT(sizeInBytes <= static_cast<std::size_t>(bufferSize));
	}
	#endif

	POMDOG_ASSERT(sizeInBytes > 0);
	glBufferSubData(GL_UNIFORM_BUFFER, offsetInBytes, sizeInBytes, source);

	#ifdef DEBUG
	ErrorChecker::CheckError("glBufferSubData", __FILE__, __LINE__);
	#endif
}
//-----------------------------------------------------------------------
void ConstantBufferGL4::Apply(std::uint32_t slotIndex)
{
	POMDOG_ASSERT(bufferObject);

	#if defined(DEBUG) && !defined(NDEBUG)
	{
		static auto const maxUniformBufferBindings = ([] {
			GLint value = 0;
			glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &value);
			return value;
		})();

		POMDOG_ASSERT(slotIndex < static_cast<std::uint32_t>(maxUniformBufferBindings));
	}
	#endif

	glBindBufferBase(GL_UNIFORM_BUFFER, slotIndex, bufferObject->value);
}
//-----------------------------------------------------------------------
}// namespace GL4
}// namespace RenderSystem
}// namespace Detail
}// namespace Pomdog
