#pragma once

class Identifiable
{
public:
    virtual ~Identifiable() {};
    virtual const __int64& getId() const = 0;
};
