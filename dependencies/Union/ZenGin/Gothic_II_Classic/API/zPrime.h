// Supported with union (c) 2018-2021 Union team

#ifndef __ZPRIME_H__VER2__
#define __ZPRIME_H__VER2__


  // sizeof 01h
  class zCPrime {
  public:

    zCPrime() {}
    static int IsPrime( unsigned long )             zCall( 0x005BA040 );
    static unsigned short PrimeNo( unsigned short ) zCall( 0x005BA110 );
    static unsigned long NextPrime( unsigned long ) zCall( 0x005BA220 );

    // user API
    #include "zCPrime.inl"
  };

#endif // __ZPRIME_H__VER2__