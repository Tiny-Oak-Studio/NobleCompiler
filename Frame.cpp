#include "Frame.h"

#include <bits/ranges_base.h>

namespace Noble::Compiler
{
    void Frame::WriteOp(const Op::Type &op)
    {
        ops.Add(op);
    }

    Address::Single Frame::WriteAddress(const Address::Single &address)
    {
        ops.Add(Translation::AddressToOps(address));
        return ops.Count() - Translation::OpsPerAddress;
    }

    void Frame::WriteAddress(const Address::Single &address, const Address::Single &addressIndex)
    {
        const List<Op::Type> addressOps = Translation::AddressToOps(address);
        for (int i = 0; i < addressOps.Count(); ++i)
        {
            ops[i + addressIndex] = addressOps[i];
        }
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

    const List<Op::Type>& Frame::GetOps() const
    {
        return ops;
    }

    const List<ValueType>& Frame::GetConstants() const
    {
        return constants;
    }
}
