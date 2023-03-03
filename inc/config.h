/**
 *  \file config.h
 *  \brief Basic SGDK library configuration file
 *  \author Stephane Dallongeville
 *  \date 08/2011
 *
 * This unit is used to define some specific compilation option of the library.
 */

#ifndef _CONFIG_
#define _CONFIG_


/**
 *  \brief
 *      Set it to 1 to enable KDebug logging (Gens KMod) for some errors (as memory allocation).
 */
#if (DEBUG == 1)
  #define LIB_DEBUG         1
#else
  #define LIB_DEBUG         0
#endif

/**
 *  \brief
 *      Set it to 1 if you want to force Z80 halt during DMA operation.<br>
 *      Some Megadrive models (as 2016 Tectoy Megadrive) need it to prevent some possible 68000 memory or Z80 corruption bugs
 *      (may happen when Z80 access the main BUS during a DMA operation).
 */
#define HALT_Z80_ON_DMA     0

/**
 *  \brief
 *      Set it to 1 if you want to force Z80 halt during IO port (controller) accesses.<br>
 *      Some Megadrive models (as some MD2) need it to prevent some possible Z80 corruption bugs
 *      (may happen when Z80 access the main BUS during IO port access from 68K).
 */
#define HALT_Z80_ON_IO      0

/**
 *  \brief
 *      Set it to 1 if you want to use newlib with SGDK.<br>
 *      That will disable any standard methods from SGDK to replace them by newlib library implementation.
 */
#define ENABLE_NEWLIB       0

/**
 *  \brief
 *      Set it to 1 to enable the big Math lookup tables.<br>
 *      This table permits Log2, Log10 and Sqrt operation for fix16 type (128*3 KB of rom).
 */
#define MATH_BIG_TABLES     0

/**
 *  \brief
 *      Set it to 1 if you want to use FAT16 methods provided by Krik.<br>
 *      This cost a bit more than 1 KB of RAM.
 */
#define FAT16_SUPPORT       0

/**
 *  \brief
 *      Set it to 1 if you want to have the kit intro logo
 */
#define ENABLE_LOGO         0

#if (ENABLE_LOGO != 0)

/**
 *  \brief
 *      Set it to 1 if you want zoom intro logo effect instead of classic fading
 */
#define ZOOMING_LOGO        0

#endif // ENABLE_LOGO


#endif // _CONFIG_
