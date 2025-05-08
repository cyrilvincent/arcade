/*\
 * INTEL hex <-> binary file Converter.
 * 
 * T.Bohning 
 * 11851 NW 37 Place
 * Sunrise, FL 33323
 * 
 * Compiler: Microsoft C 5.1
 * 2/20/89
 * 
 * Compuserve User ID: [71036,1066]
 * GEnie address: T.BOHNING
 * 
INTEL hex description:
8 bit codes are split into two nibbles, and each nibble stored as 
a hex ascii digit '0' through 'F'.
Each line of the intel hex file is a record, with the following format:

    <junk>:NNAAAATTD1D2D3D4....DnCC<junk><eol>

The colon means start of record, NN is the number of data bytes in the 
record given as two hex digits.  AAAA is the starting load address of
the record.  
*
TT is a record type, 00 for data records.  D1,D2...Dn are the hex ASCII 
representations of the data bytes.  CC is a hex ASCII checksum, chosen
such that it's sum with all preceding byte values in the record 
(not just the data bytes) modulo 256 = 0.
*
The end of the hex file is marked by a record with a data length of 0
and a record type of 01.  The address in the end record can be the
entry address for an executable, or 0000.
*
* This description is for "old" INTEL hex, which could only support
* 64K loads.  "Extended" INTEL hex was developed when the 8086 came
* along.
\*/

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

#ifndef BAD_OPEN
#define BAD_OPEN NULL
#endif

#define stdrpt stdout
#define stdctl stdin

enum bool { FALSE = 0, TRUE };

/*\
 * Global variables -
\*/
unsigned int RecLen;            /* FJS bytes per line */

/*\
 * function prototypes -
\*/
void    genbin( FILE *inptr, FILE *outptr, unsigned int offset);
void    genhex( FILE *inptr, FILE *outptr, unsigned int load_addr);
int     get_yn( char *msg );
int     get_hexbyte( char *cptr );
int     hexext( char *filename );
int     main( int argc, char *argv[] );
char *  put_hexbyte( char *cptr, int val );
void	read_exit( void );
void    trouble( char *msg, int n );
void    usexit( int t );
void 	write_exit( void );

/* file i/o buffer size (2 allocated)
*/
#define	FILE_BUFSIZE	0x6000

/*\
 * report error and exit
\*/
void
trouble( msg, n ) char *msg; int n; {
    if ( msg /* != NULL */ ) fprintf(stdrpt, "\n%s", msg);
    putc('\n', stdrpt);
    exit(n);
}


/*\
 * read error on input file
\*/
void
read_exit() { trouble("Error on input file read\n", 11); }


/*\
 * write error on output file
\*/
void
write_exit() { trouble("Error on output file write\n", 13); }

/*\
 * Get a byte from hex ascii string, return the value.
\*/
int 
get_hexbyte( cptr ) char *cptr;
{
register int j;
char prev, nbl;
	
    nbl = 0;
    for( j = 2; j-- /* != 0 */; ++cptr) {
        prev = nbl;
        if ((*cptr >= '0') && (*cptr <= '9')) { /* ASCII!!! */
			nbl = *cptr - '0';
        } else if ((*cptr >= 'A') && (*cptr <= 'F')) {
            nbl = *cptr - ('A' - 10);  
        } else if ((*cptr >= 'a') && (*cptr <= 'f')) {
            nbl = *cptr - ('a' - 10);  
        } else {
            trouble("Hex file contains invalid character\n", 6);
		}
	}
    return( (prev << 4) + nbl ) & 255;
}


/*\
 *   Convert INTEL hex from infile to binary in outfile.
\*/
#define MOD_LIMIT   0xFF    /* report interval */

void
genbin( inptr, outptr, offset)
FILE *inptr, *outptr;
unsigned int offset;
{
char *bufptr;
int i;
int linenum;
int numbytes;
unsigned int load_addr, next_addr, modcnt;
char linebuf[257];                              /* input buffer */
char chksum, c;
	
    modcnt  = 0;
    linenum = 1;
    next_addr = offset;

    fputs("Processing hex file line number:     1", stdrpt);
    fflush(stdrpt);

	/*\
	 * process input file 1 line at a time.
	\*/
    for ( ; fgets( linebuf, sizeof(linebuf)-1, inptr) > 0; ++linenum ) {
        bufptr = linebuf;

        while ( ( (c = *bufptr) != 0 /* EOS */)
                && (c != '\n') && (c != ':') )
            ++bufptr;           /* allow and skip any leading junk */

        if ( c == '\n' ) continue;      /* skip comment & blank lines */

		if ( *bufptr++ != ':' ) {
            fprintf(stdrpt, "\nIntel hex format error in line %d\n",
                linenum);
            exit(7);
		}		

		/*\
         * Get number of data bytes and put into checksum.
		\*/
		numbytes = get_hexbyte( bufptr );
        chksum = (char)numbytes;
		bufptr += 2;

		/*\
		 * Add load address and record type into checksum.
		\*/
        chksum += (c = get_hexbyte( bufptr ));
        bufptr += 2;
        load_addr = c & 255;
        chksum += (c = get_hexbyte( bufptr ));
        bufptr += 2;
        load_addr = (load_addr << 8) + (c & 255);

        chksum += (c = get_hexbyte( bufptr )); /* record type */
        bufptr += 2;
        if (numbytes /* != 0 */ && c /* != 0 */) {
            fprintf(stdrpt,
                    "\nCan't process type 0x%02X record in line %d\n",
                    c & 255, linenum);
            exit(8);
        }
		
		/*\
		 * Write the binary data.
		\*/
        for ( i = numbytes; i-- /* != 0 */; /* nil */) {
			c = get_hexbyte(bufptr);
			bufptr += 2;

            if ( load_addr != next_addr )
                if (load_addr < offset) {
                    fprintf(stdrpt,
                "\nLoad address (0x%04X) < offset (0x%4X) in line %d\n",
                            load_addr, offset, linenum);
                    exit(14);
                }

                fseek(outptr, (long)(load_addr - offset),
                    0 /* FROM_START */);

            putc(c, outptr);
			chksum += c;
            next_addr = ++load_addr;
		}

        if ( ferror( outptr ) ) write_exit();

		/*\
		 * Sum in checksum byte and check the sum.
		\*/
		chksum += get_hexbyte(bufptr);
		if (chksum != 0) {
            fprintf(stdrpt, "\nChecksum error in line %d\n", linenum);
            exit(9);
		}

        if ( numbytes == 0 ) {                  /* end of hex file */
            /* we ignore any trailing junk in file tail */
            fprintf(stdrpt, "\b\b\b\b\b%5d\n", linenum);
            return;
		}								

        if ( (modcnt += numbytes) > MOD_LIMIT ) { /* report */
            fprintf(stdrpt, "\b\b\b\b\b%5d", linenum);
            fflush(stdrpt);
            modcnt &= MOD_LIMIT;
		}

        /* we ignore any trailing junk in line tail */
    } /* end while line read */   

    if (ferror(inptr)) read_exit();

    trouble(
  "Warning: Terminator record not found, hex file probably truncated.\n"
        , 10);
}


/*\
 * Put a byte as hex ascii, return pointer to next location.
\*/
char *
put_hexbyte(cptr, val) char *cptr; int val;
{
static char hextbl[16] = {
		'0', '1', '2', '3', '4', '5', '6', '7', 
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
	};
	
	*cptr++ = hextbl[ ((val >> 4) & 0x0F) ];

	*cptr++ = hextbl[ val & 0x0F ];

	return(cptr);	
}


/*\
 *   Convert binary from infile to INTEL hex in outfile.
\*/
void
genhex( inptr, outptr, load_addr) 
FILE *inptr, *outptr;
unsigned int load_addr;
{
#define DATA_BYTES  0x20    /* max data bytes per record */

    /* hex file line buffer, one space for EOS, 
    * one space for \n, ...
    *                           :  len addr 00 cks \n  EOS */
char    hexline[ DATA_BYTES*2 + 1 + 2 + 4 + 2 + 2 + 1 + 1 ]; 
char    data_buf[ DATA_BYTES ];

int numbytes, i, modcnt;
unsigned int linenum, c;
char *bufptr;
unsigned char chksum;
	
    modcnt  = 0;
    linenum = 1;

	hexline[0] = ':';	/* colon always starts a record */
	hexline[7] = '0';	/* type for data records is */
    hexline[8] = '0';   /* ... "00" */

    fputs("Processing hex file line number:     1", stdrpt);
    fflush(stdrpt);

	/*\
	 * Build a line 
	\*/
    while( (numbytes = fread( data_buf, sizeof(char), RecLen, inptr))
            > 0 )  {
		
		/*\
		*  Write out all the bytes as hex,
		*   updating chechksum as we go.
		\*/
		bufptr = &hexline[1];	/* skip the colon */

		chksum = (char)numbytes;
        bufptr = put_hexbyte( bufptr, numbytes );

		chksum += (char)(load_addr >> 8);
		chksum += (char)load_addr;

        bufptr = put_hexbyte( bufptr, (load_addr >> 8) );
        bufptr = put_hexbyte( bufptr, load_addr );

		bufptr += 2;	/* skip over data record type */

		/*\
		 * Write out actual data bytes.
		\*/
        for ( i = 0; i < numbytes; ++i) {
            chksum += (c = data_buf[i]);
            bufptr = put_hexbyte( bufptr, c );
        }

		chksum = ~chksum+1;
        bufptr = put_hexbyte( bufptr, chksum );

		*bufptr++ = '\n';
        *bufptr = 0 /* EOS */;

		/*\
		 * write this line of the hex file
		\*/
		fputs( hexline, outptr );

        if ( ferror(outptr) ) write_exit();

		load_addr += numbytes;

		++linenum;
        if ( (modcnt += numbytes) > MOD_LIMIT ) {
            fprintf(stdrpt, "\b\b\b\b\b%5d", linenum);
            fflush(stdrpt);
            modcnt &= MOD_LIMIT;
		}
	}
    fprintf(stdrpt, "\b\b\b\b\b%5d\n", linenum);

    if ( ferror(inptr) ) read_exit();

    fputs(":00000001FF\n", outptr);   /* Standard termination record */
    /* return; */
}


/*\
 *  Try to find .HEX extension on a filename.
\*/
hexext( cptr )
char *cptr; {
int n;

    /* FJS no match if too short for name and extension - */
    n = strlen(cptr);
    if ( n < 5 ) return 0 /* FALSE */;

    return( stricmp( cptr + (n - 4), ".hex") == 0 /* SAME */ );
}


/*\
 * Print msg, Get y or n from user.  
 * Return upper case variant.
\*/
int 
get_yn( msg ) char *msg;
{
int c;

    do {
        fputs( msg, stdrpt);
        fflush(stdrpt);
        c = getc(stdctl);
        putc('\n', stdrpt);

        if ( (c == 'y') || (c == 'Y') ) return( 'Y' );

    } while ( (c != 'n') && (c != 'N') ) ;

    return( 'N' );
}


/*\
 * Show usage and die.
\*/
void
usexit( t ) int t; {
    if ( t )
        fputs("\nINTEL hex <-> binary file converter\n", stdrpt);

    fputs("\nUsage: HEXBIN [+n] [(- | /) (m | help)] infile outfile\n",
            stdrpt);

    if ( t ) {
        fputs(
            "\nOne (only) of infile or outfile must have .HEX extension"
                , stdrpt);
        fputs("\ndefaults: offset (n) = 256, Record size (m) = 16\n",
                stdrpt);
        fputs("\n"
  "If infile  has .HEX extension, HEX to binary conversion is performed"
                , stdrpt);
        fputs("\n"
  "If outfile has .HEX extension, binary to HEX conversion is performed"
                , stdrpt);
    }
    exit(12);
}

int
main( argc, argv) int argc; char *argv[];
{
FILE *inptr, *outptr;
int tohex;                      /* TRUE -> binary to HEX */
unsigned int offset;            /* FJS offset or load address */
char *inbuf, *outbuf;           /* file I/O buffers */
char c;
	
	/*\
 	 * Check args.
	\*/
    if ( argc < 3 ) usexit( 0 );                /* FJS default help */

    offset = 256 /* 0x100 */;                           /* default */
    RecLen =  16 /* 0x010 */;                           /* default */

    while ( ( (c = *(argv[1])) == '+')  /* FJS option(s) given */
            || (c == '-') || (c == '/') ) {
    char *cp;

        --argc; cp = (*++argv) + 1;     /* advance option list */
        if ( c == '+' ) {               /* FJS offset option given */
            offset = (unsigned int)strtol(cp, (char **)NULL, 0);
        } else {        /* FJS help or record-length option given */
            if ( ((c = *cp) == 'H') || (c == 'h') || (c == '?') )
                usexit( 1 );                    /* help requested */

            RecLen = (unsigned int)strtol(cp, (char **)NULL, 0);
            if ( (RecLen < 4) || (RecLen > 32) ) {
                fprintf(stdrpt,
                        "Record length (%d) should be between 4 and 32",
                        RecLen);
                exit(15);
            }
        }
    }
	
    if (argc != 3) usexit( 1 );                 /* help needed */
	
	/*\
     * Open files, check for (1) .HEX extension, establish 
	 * conversion direction.
	\*/
    if ( (tohex = hexext(argv[2])) == hexext(argv[1]) )
        usexit( 1 ); /* help needed */

	/*\
	 * Open the files.
	\*/
    if ( (inptr = fopen( argv[1], tohex ? "rb" : "rt" )) == BAD_OPEN ) {
        fprintf(stdrpt, "can't open %s for reading", argv[1]);
        exit(1);
    }

	/*\
	 * Test for output file existence first.
	\*/
    if ( (outptr = fopen( argv[2], "rb" )) != BAD_OPEN ) {

        if ( get_yn("Output file exists, overwrite (Y/N)? ") == 'N' )
            exit(2);

        fclose( outptr );
	}
    if ( (outptr = fopen( argv[2], tohex ? "wt" : "wb" )) == BAD_OPEN ) {
        fprintf(stdrpt, "can't open %s for writing", argv[2]);
        exit(3);
	}

	/*\
	 * Allocate and set up file I/O buffers
	\*/
    if (   ( (inbuf = malloc( FILE_BUFSIZE)) == NULL) 
           || ( (outbuf = malloc( FILE_BUFSIZE)) == NULL)
       ) {
        trouble("Can't allocate file I/O buffers", 4);
	}

    if (   setvbuf( inptr, inbuf, _IOFBF, FILE_BUFSIZE )
           || setvbuf( outptr, outbuf, _IOFBF, FILE_BUFSIZE )
       ) {
        trouble("Error setting file buffers", 5);
	}

    fprintf(stdrpt, "Converting: %s -> %s\n", argv[1], argv[2] );
	if (tohex) {
        genhex(inptr, outptr, offset);
	} else {
        genbin(inptr, outptr, offset);
	}
    return 0 /* OK */;
}


/************************ EOF *************************/

