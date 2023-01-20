#ifndef CAPYCITY_MATERIAL_H
#define CAPYCITY_MATERIAL_H

class Material
{
protected:
    int _cost;
    char *_name;

protected:
    Material(int cost, char *name);

public:
    char *getName() const;

    int getCost() const;
};

class Wood : public Material
{
private:
    static Wood *_wood;
    Wood();

public:
    static Wood *getInstance();
};

class Plastic : public Material
{
private:
    static Plastic *_plastic;
    Plastic();

public:
    static Plastic *getInstance();
};

class Metal : public Material
{
private:
    static Metal *_metal;
    Metal();

public:
    static Metal *getInstance();
};
#endif // CAPYCITY_MATERIAL_H