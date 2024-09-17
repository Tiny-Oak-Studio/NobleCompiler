#ifndef NOBLE_CORE_FRAME_H_INCLUDED
#define NOBLE_CORE_FRAME_H_INCLUDED

#include <stdint.h> //Use old header for Arduino compatibility
#include "NobleCore/Value.h"
#include "NobleCore/List.h"
#include "NobleCore/Op.h"
#include "NobleCore/Translation.h"

using namespace Noble::Core::Runtime;
using namespace Noble::Core;

namespace Noble::Compiler
{
    /// @brief Contains Noble Assembly Language Sequence (NAL) information and translation methods.
    class Frame
    {
    public:
        /// @brief Writes an op to this frame's underlying array
        void WriteOp(const Op::Type& op);

        /// @brief Writes an address into the frame's underlying array
        void WriteAddress(const Address::Single& address);

        /// @brief Writes the value to the ops array.
        void WriteConstant(ValueType value);

        /// @brief Returns the op at the specified address
        [[nodiscard]] Op::Type ReadOp(const Address::Single& address);

        /// @brief Reads ops from the specified address and returns them as an address
        [[nodiscard]] Address::Single ReadAddress(const Address::Single &address) const;

        /// @brief Reads a constant at the given address.
        [[nodiscard]] const ValueType& ReadConstant(Address::Single address) const;

        /// @brief Adds a constant to this frame
        Address::Single AddConstant(ValueType value);

        /// @brief Get a const ref to the ops array
        [[nodiscard]] const List<Op::Type>& GetOps() const;

        /// @brief Get a const ref to the constants array
        [[nodiscard]] const List<ValueType>& GetConstants() const;
    protected:
        /// @brief Storage for reading/writing ops in the compiler
        List<Op::Type> ops;

        /// @brief Storage for the constants used in this frame
        List<ValueType> constants;
    };
}

#endif //NOBLE_CORE_FRAME_H_INCLUDED