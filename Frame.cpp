#include "Frame.h"

namespace Noble::Compiler
{
    void Frame::WriteOp(const Op::Type &op)
    {
        ops.Add(op);
    }

    void Frame::WriteAddress(const Address::Single &address)
    {
        ops.Add(Translation::AddressToOps(address));
    }

    void Frame::WriteConstant(const ValueType value)
    {
        WriteOp(Op::Code::Constant);
        WriteAddress(AddConstant(value));
    }

    Op::Type Frame::ReadOp(const Address::Single& address)
    {
        return ops[address];
    }

    Address::Single Frame::ReadAddress(const Address::Single &address) const
    {
        return Translation::OpsToAddress(ops, address);
    }

    const ValueType& Frame::ReadConstant(const Address::Single address) const
    {
        return constants[address];
    }

    Address::Single Frame::AddConstant(const ValueType value)
    {
        constants.Add(value);
        return constants.Count() - 1;
    }

    Address::Single Frame::NumOps() const
    {
        return ops.Count();
    }

    Address::Single Frame::NumConstants() const
    {
        return constants.Count();
    }

    const List<Op::Type>& Frame::GetOps() const
    {
        return ops;
    }

    const List<ValueType>& Frame::GetConstants() const
    {
        return constants;
    }
}
