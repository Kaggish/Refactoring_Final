#include <iostream>
#include <string_view>
#include <stdexcept>
#include <format>
#include "raylib.h"

using namespace std::literals::string_view_literals;

struct TextureData 
{
    Texture2D m_texture;
    explicit TextureData(std::string_view path) 
    {
        m_texture = LoadTexture(path.data());
        if (m_texture.id <= 0) 
        {
            throw(std::runtime_error(std::format("Unable to load texture: {}"sv, path)));
        }
    };

    TextureData(const TextureData& other) = delete;
    TextureData& operator=(const TextureData& other) = delete;

    TextureData(TextureData&& other) noexcept 
    {
        std::swap(other.m_texture, m_texture);
    }

    TextureData& operator=(TextureData&& other) noexcept 
    {
        if (this != &other) 
        {
            std::swap(other.m_texture, m_texture);
        }
        return *this;
    }

    ~TextureData() 
    {
        UnloadTexture(m_texture);
    };

    const Texture2D& get() const noexcept 
    {
        return m_texture;
    }
};

struct Resources
{
    std::vector<TextureData> shipTextures;
    Resources() 
    {
        shipTextures.emplace_back("./Assets/Ship1.png"sv);
        shipTextures.emplace_back("./Assets/Ship2.png"sv);
        shipTextures.emplace_back("./Assets/Ship3.png"sv);
    }

    TextureData alienTexture = TextureData("./Assets/Alien.png"sv);
    TextureData barrierTexture = TextureData("./Assets/Barrier.png"sv);
    TextureData laserTexture = TextureData("./Assets/Laser.png"sv);
};