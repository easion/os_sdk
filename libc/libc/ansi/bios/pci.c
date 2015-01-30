#define JICAMA
#include <stdio.h>
#include <string.h>
#include <sys/farptr.h>
#include <int86.h>
#include <bios.h>

int pci_inst_check( void )
{
  vm86regs_t rm;

  memset( &rm, 0, sizeof( rm ) );

  rm.x.ax = 0xb101;

  realint( 0x1a, &rm );
	
  if (  (rm.x.ax & 0xff00) == 0 )
  {
/*		printf( "ID              = %0x (%4s)\n", rm.EDX, &rm.EDX ); */
    printf( "PCI Characteristics = %lx\n", rm.x.ax & 0xff );
    printf( "PCI Version         = %ld.%ld\n", rm.x.bx >> 8, rm.x.bx & 0xff );
    printf( "Last PCI bus        = %ld\n", rm.x.cx & 0xff );
		
    return( (rm.x.cx & 0xff) + 1 );
  }
  else
  {
    printf( "PCI installation check failed\n" );
    return( -1 );
  }
	
}

unsigned long read_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize )
{
  vm86regs_t rm;

  if ( 2 == nSize || 4 == nSize || 1 == nSize )
  {
    int	anCmd[] = { 0xb108, 0xb109, 0x000, 0xb10a };
    unsigned long	anMasks[] = { 0x000000ff, 0x0000ffff, 0x00000000, 0xffffffff };
    memset( &rm, 0, sizeof( rm ) );

    rm.x.ax = anCmd[nSize - 1];

    rm.x.bx = (nBusNum << 8) | (((nDevNum << 3) | nFncNum));
    rm.x.di = nOffset;
		

    realint( 0x1a, &rm );

    if ( 0 == ((rm.x.ax >> 8) & 0xff) ) {
      return( rm.x.cx & anMasks[ nSize- 1 ] );
    } else {
      return( anMasks[ nSize- 1 ] );
    }
  }
  else
  {
    printf( "ERROR : Invalid size %d passed to read_pci_config()\n", nSize );
    return( 0 );
  }
}

int write_pci_config( int nBusNum, int nDevNum, int nFncNum, int nOffset, int nSize, unsigned long nValue )
{
  vm86regs_t rm;

  if ( 2 == nSize || 4 == nSize || 1 == nSize )
  {
    int	anCmd[] = { 0xb10b, 0xb10c, 0x000, 0xb10d };
    unsigned long	anMasks[] = { 0x000000ff, 0x0000ffff, 0x00000000, 0xffffffff };
    memset( &rm, 0, sizeof( rm ) );

    rm.x.ax = anCmd[nSize - 1];

    rm.x.bx = (nBusNum << 8) | (((nDevNum << 3) | nFncNum));
    rm.x.di = nOffset;
    rm.x.cx = nValue & anMasks[ nSize - 1 ];

    realint( 0x1a, &rm );

    return(0 );
  }
  else
  {
    printf( "ERROR : Invalid size %d passed to write_pci_config()\n", nSize );
    return( -1 );
  }
}
