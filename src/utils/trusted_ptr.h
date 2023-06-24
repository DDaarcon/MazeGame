#pragma once

#include <memory>

template <class _Ty>
class trusted_ptr {
public:
    _Ty* operator->() const noexcept 
    {
        return _pointer;
    }

    bool operator==(const trusted_ptr& other) const
    {
        return _pointer == other._pointer;
    }

    bool operator==(const _Ty* other) const 
    {
        return _pointer == other;
    }

    operator _Ty* () const 
    {
        return _pointer;
    }

    trusted_ptr() = delete;
    trusted_ptr(_Ty* pointer)
        : _pointer(pointer)
    { }
private:
    _Ty* _pointer;
};