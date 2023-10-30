// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
    {
        throw;
    }
    BitLen = len;
    MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = (TELEM)0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (BitLen == 0) {
        pMem = nullptr;
    }
    else
    {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

TBitField::~TBitField()
{
    BitLen = 0;
    MemLen = 0;
    if (pMem != nullptr)
    {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM mask;
    mask = 1;
    return mask << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw;
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    pMem[index] = mask | pMem[index];
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw;
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    mask = ~mask;
    pMem[index] = pMem[index] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
    {
        throw;
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    if ((pMem[index] & mask) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (bf.pMem != pMem)
    {
        if (MemLen != bf.MemLen)
        {
            delete[] pMem;
            pMem = new TELEM[bf.MemLen];
        }
        MemLen = bf.MemLen;
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return false;
    }
    int current_mem_index = MemLen - 1;
    for (int i = 0; i < current_mem_index; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return false;
        }
    }

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bf == *this)
    {
        return 0;
    }
    else
    {
        return 1;
    }
  
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

    TBitField bitfield = TBitField(BitLen);
    for (size_t i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return bitfield;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField bitfield = TBitField(BitLen);
    for (size_t i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return bitfield;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField bitfield = TBitField(BitLen);
    for (size_t i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = ~pMem[i];
    }
    return bitfield;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit = 0;
    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> bit;
        if (bit == 0)
        {
            bf.ClrBit(i);
        }
        else
        {
            bf.SetBit(i);
        }
        
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        std::cout << bf.GetBit(i);
    }
    return ostr;
}


// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests

TBitField::TBitField(int len)
{
    if (len < 0) throw exception();

    BitLen = len;
    MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = (TELEM)0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    if (BitLen == 0) {
        pMem = nullptr;
    }
    else
    {
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
}

TBitField::~TBitField()
{
    BitLen = 0;
    MemLen = 0;
    if (pMem != nullptr)
    {
        delete[] pMem;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM mask;
    mask = 1;
    return mask << n;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw exception();
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    pMem[index] = mask | pMem[index];
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n >= BitLen)
    {
        throw exception();
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    mask = ~mask;
    pMem[index] = pMem[index] & mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
    {
        throw exception();
    }
    int index = n / (sizeof(TELEM) * 8);
    int bitNumber = n - index * (sizeof(TELEM) * 8);
    TELEM mask = 1;
    mask = mask << bitNumber;
    if ((pMem[index] & mask) != 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (bf.pMem != pMem)
    {
        if (MemLen != bf.MemLen)
        {
            delete[] pMem;
            pMem = new TELEM[bf.MemLen];
        }
        MemLen = bf.MemLen;
        BitLen = bf.BitLen;
        for (int i = 0; i < MemLen; i++)
        {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return false;
    }
    for (int i = 0; i < MemLen; i++)
    {
        if (pMem[i] != bf.pMem[i])
        {
            return false;
        }
    }
    return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (bf == *this)
    {
        return 0;
    }
    else
    {
        return 1;
    }
  
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int maxBitLen;
    if (BitLen > bf.BitLen)
    {
        maxBitLen = BitLen;
    }
    else
    {
        maxBitLen = bf.BitLen;
    }
    TBitField bitfield = TBitField(maxBitLen);
    for (size_t i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = pMem[i] | bf.pMem[i];
    }
    return bitfield;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int maxBitLen;
    if (BitLen > bf.BitLen)
    {
        maxBitLen = BitLen;
    }
    else
    {
        maxBitLen = bf.BitLen;
    }
    TBitField bitfield = TBitField(maxBitLen);
    for (size_t i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return bitfield;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField bitfield = TBitField(BitLen);
    for (int i = 0; i < MemLen; i++)
    {
        bitfield.pMem[i] = ~pMem[i];
    }
    if (BitLen % (sizeof(TELEM) * 8) != 0)
    {
        TELEM mask = 0;
            mask = ~mask;
            mask = mask >> (sizeof(TELEM) * 8 - (BitLen % (sizeof(TELEM) * 8)));
            bitfield.pMem[MemLen - 1] = bitfield.pMem[MemLen - 1] & mask;
    }
    return bitfield;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int bit = 0;
    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> bit;
        if (bit == 0)
        {
            bf.ClrBit(i);
        }
        else
        {
            bf.SetBit(i);
        }
        
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        std::cout << bf.GetBit(i);
    }
    return ostr;
}
