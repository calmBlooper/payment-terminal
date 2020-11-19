#pragma once

class Identifiable
{
public:
    virtual ~Identifiable() {};
    virtual const long long& getId() const = 0;
};