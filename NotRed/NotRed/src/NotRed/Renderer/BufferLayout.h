#pragma once

namespace NR
{
    enum class ShaderDataType : int8_t
    {
        None, Float, Float2, Float3, Float4, Int, Mat3, Mat4
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float:   return 4;
        case ShaderDataType::Float2:  return 4 * 2;
        case ShaderDataType::Float3:  return 4 * 3;
        case ShaderDataType::Float4:  return 4 * 4;
        case ShaderDataType::Int:     return 4;
        case ShaderDataType::Mat3:    return 4 * 3 * 3;
        case ShaderDataType::Mat4:    return 4 * 4 * 4;
        default:
        {
            NR_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
        }
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() = default;
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            :Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {
        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
            case ShaderDataType::Float:   return 1;
            case ShaderDataType::Float2:  return 2;
            case ShaderDataType::Float3:  return 3;
            case ShaderDataType::Float4:  return 4;
            case ShaderDataType::Int:     return 4;
            case ShaderDataType::Mat3:    return 3 * 3;
            case ShaderDataType::Mat4:    return 4 * 4;
            default:
            {
                NR_CORE_ASSERT(false, "Unknown ShaderDataType!");
                return 0;
            }
            }
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : mElements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline const std::vector<BufferElement>& GetElements() const { return mElements; };

        inline const uint32_t GetStride() const { return mStride; }

        std::vector<BufferElement>::iterator begin() { return mElements.begin(); }
        std::vector<BufferElement>::iterator end() { return mElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return mElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return mElements.end(); }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            mStride = 0;
            for (auto& element : mElements)
            {
                element.Offset = offset;
                offset += element.Size;
                mStride += element.Size;
            }
        }

    private:
        std::vector<BufferElement> mElements;
        uint32_t mStride;
    };
}