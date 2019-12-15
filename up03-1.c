int bitcount(STYPE value)
{
    UTYPE uns = (UTYPE) value;
    int count = 0;
    int bit;
    while (uns) {
        bit = uns & 1;
        uns >>= 1;
        if (bit) {
            count++;
        }
    }
    return count;
}
