/*								-*-C-*-
 *	ITS filesystem definitions
 *
 *	Defines the format of binary MFDs and UFDs for use by C programs.
 */

/*
**  MFD INFO
*/

		/* RANDOM INFO IN MFD */

#define MDNUM 0		/* ASCENDING DIR NUM */
#define MDNAMP 1	/* PNTR TO ORG OF USER NAME BLOCK AREA */
#define MDYEAR 2	/* CURRENT YEAR */
#define MPDOFF 3	/* DE-CORIOLIS CLOCK OFFSET */
#define MPDWDK 4	/* PREFERRED WRITING DISK (PHYSICAL DRIVE #) */
#define MDCHK 5		/* THIS WORD MUST BE M.F.D. (FOR CHECKING) */
#define MDNUDS 6	/* NUMBER USER DIRECTORIES (FOR CHECKING ONLY) */
#define LMIBLK 7	/* TOTAL STG USED BY HACKS LIKE THIS */

		/* USER NAME BLKS FROM C(MDNAMP) TO END */

#define LMNBLK 2	/* # WDS/BLK */
#define MNUNAM 0	/* 6BIT USER NAME */

/*
** UFD INFO
*/

#define UFDBYT 6		/* SIZE OF BYTES */
#define UFDBPW (36 / UFDBYT)	/* NUMBER OF BYTES PER WORD */

		/* RANDOM INFO IN UFD */

#define UDESCP 0	/* FS PNTR TO DESC AREA */
#define UDNAMP 1	/* PNTR TO ORG OF NAME AREA */
#define UDNAME 2	/* USER NAME (FOR CHECKING) */
#define UDBLKS 3	/* LEFT HALF HAS AMOUNT OF SPACE ALLOCATED (NOT */
			/* USED CURRENTLY BY SYSTEM), RIGHT HALF HAS */
			/* NUMBER OF BLOCKS USED. */
#define UDALLO 4	/* IF NONZERO, LEFT HALF HAS DISK NUMBER, RIGHT */
			/* HALF HAS AMOUNT OF SPACE ALLOCATED */
#define UDDESC 11	/* FIRST LOC AVAIL FOR DESC */

	/* UFD DESCRIPTORS
	** 0 => FREE  1-UDTKMX => TAKE NEXT N
	** UDTKMX+1 THRU UDWPH-1 => SKIP N-UDTKMX AND TAKE ONE
	** UDWPH => WRITE-PLACE-HOLDER
	** 040 BIT SET => LOAD ADDRESS.  LOWER 5 BITS PLUS NEXT NXLBYT (2)
	**   CHARS (17 BITS IN ALL)
	** 040 BIT & 020 BIT => "FUNNY" BLOCK IF DMDSK.  WHAT IS THIS, ANYWAY?
	** END BY 0
	**
	** IF LINK DESCR
	** 6 CHAR OR UNTIL ; = SYS NAME.  MUST HAVE NO CHAR = 0 IN THIS OR
	**   NEXT 2 NAMES
	** NEXT CHAR QUOTED BY : (FOR NAMES WITH : OR ;)
	** NEXT CHAR N1
	** NEXT CHAR N2
	** END BY 0
	*/

#define UDTKMX 12		/* HIGHEST "TAKE N" CODE */
#define UDWPH 31		/* PLACE HOLDER ON WRITE (OR NULL FILE) */
#define UDSKMX (UDWPH - UDTKMX - 1)	/* # BLOCKS THAT CAN BE SKIPPED */
#define NXLBYT 2		/* # ADDITIONAL BYTES FOR LOAD ADDR */

		/* NAME AREA DATA */

#define LUNBLK 5	/* WDS/NAME BLK */
#define UNFN1 0		/* FIRST FN */
#define UNFN2 1		/* SECOND FN */
#define UNRNDM 2	/* ALL KINDS OF RANDOM INFO */
#define  UNDSCP	0001500000000	/* PNTR TO DESC */
#define  UNPKN	0150500000000	/* PACK # */
#define  UNLINK      01000000	/* LINK BIT */
#define  UNREAP	     02000000	/* IF 1, DONT REAP FILE */
#define  UNWRIT	     04000000	/* OPEN FOR WRITING */
#define  UNMARK	    010000000	/* GC MARK BIT */
#define  UNCDEL	    020000000	/* DEL WHEN CLOSED */
#define  DELBTS	    020000000	/* DELETED -- IGNORE */
#define  UNIGFL	    024000000	/* BITS TO IGNORE FILE */
#define  UNWRDC	0301200000000	/* WORD COUNT OF LAST BLOCK MOD 2000 */
#define  UNDUMP	0400000000000	/* HAS BEEN DUMPED */
#define UNDATE 3	/* DATE ETC.  */
#define  UNTIM	0002200000000	/* COMPACTED TIME OF CREATION */
#define  UNYMD	0222000000000	/* Y,M,D OF CREATION */
#define  UNMON	0270400000000	/* MONTH */
#define  UNDAY	0220500000000	/* DAY */
#define  UNYRB	0330700000000	/* YEAR */
#define UNREF 4		/* REFERENCE DATE SAME AS LEFT HALF OF UNDATE */
#define  UNREFD	0222000000000	/* REFERENCE DATE */
#define  UNAUTH	0111100000000	/* MFD INDEX OF AUTHOR, ALL 1=> NO */
				/* DIRECTORY */
#define  UNBYTE	0001100000000	/* FILE BYTE SIZE AND LENGTH INFO. */
			/* LET S=BITS PER BYTE, C=COUNT OF UNUSED BYTES
			** IN LAST WD
			** 400+100xS+C	S=1 TO 3	C=0 TO 35.
			** 200+20xS+C	S=4 TO 7	C=0 TO 8
			** 44+4xS+C	S=8 TO 18.	C=0 TO 3
			** 44-S		S=19. TO 36.	C=0
			** NOTE THAT OLD FILES HAVE UNBYTE=0 => S=36.
			*/