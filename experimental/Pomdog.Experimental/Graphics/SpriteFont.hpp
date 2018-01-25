// Copyright (c) 2013-2018 mogemimi. Distributed under the MIT license.

#pragma once

#include "Pomdog/Graphics/detail/ForwardDeclarations.hpp"
#include "Pomdog/Math/detail/ForwardDeclarations.hpp"
#include "Pomdog/Math/Rectangle.hpp"
#include <cstdint>
#include <memory>
#include <vector>
#include <string>

namespace Pomdog {
namespace Detail {
namespace SpriteFonts {

struct Glyph {
    Rectangle Subrect;

    ///@note UTF-32
    char32_t Character;

    std::int16_t XOffset;
    std::int16_t YOffset;
    std::int16_t XAdvance;
    std::int16_t TexturePage;
};

} // namespace SpriteFonts
} // namespace Detail

class SpriteBatchRenderer;
class TrueTypeFont;

class SpriteFont final {
public:
    SpriteFont(
        std::vector<std::shared_ptr<Texture2D>> && textures,
        const std::vector<Detail::SpriteFonts::Glyph>& glyphs,
        char32_t defaultCharacter,
        std::int16_t spacing,
        std::int16_t lineSpacing);

    SpriteFont(
        const std::shared_ptr<GraphicsDevice>& graphicsDevice,
        const std::shared_ptr<TrueTypeFont>& font,
        char32_t defaultCharacter,
        std::int16_t lineSpacing);

    ~SpriteFont();

    Vector2 MeasureString(const std::string& text) const;

    char32_t GetDefaultCharacter() const;

    void SetDefaultCharacter(char32_t character);

    float GetLineSpacing() const;

    void SetLineSpacing(float lineSpacing);

    bool ContainsCharacter(char32_t character) const;

    void Draw(
        SpriteBatchRenderer & spriteBatch,
        const std::string& text,
        const Vector2& position,
        const Color& color);

    void Draw(
        SpriteBatchRenderer & spriteBatch,
        const std::string& text,
        const Vector2& position,
        const Color& color,
        const Radian<float>& rotation,
        float scale);

    void Draw(
        SpriteBatchRenderer & spriteBatch,
        const std::string& text,
        const Vector2& position,
        const Color& color,
        const Radian<float>& rotation,
        const Vector2& scale);

private:
    class Impl;
    std::unique_ptr<Impl> impl;
};

} // namespace Pomdog
