/* ===============================================================
  E.Incerti - Universit� Gustave Eiffel - eric.incerti@univ-eiffel.fr 
       - Librairie G3X - Fonctions de base d'acc�s public -           
                    version 6.0 - Mar.2020                                           
  ============================================================= */

#ifdef __cplusplus
  extern "C" {
#else
  #define _GNU_SOURCE
#endif

  #ifndef _G3X_H_
    #define _G3X_H_
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <math.h>
  #include <unistd.h>
  
  #include <GL/gl.h>
  #include <GL/glut.h>

  #include <g3x_types.h>      /* types primaires et macros diverses        */
  #include <g3x_utils.h>      /* macros et fonctions basiques Pts, Vect    */
  #include <g3x_tools.h>      /* utilitaires divers                        */
  #include <g3x_colors.h>     /* couleurs pr�d�finies                      */
  #include <g3x_capture.h>    /* routines de capture d'�cran image/vid�o   */
  #include <g3x_transfo.h>    /* transfo. en coordonn�es homog�nes 4x4     */
  #include <g3x_GLtransfo.h>  /* transfo. en coordonn�es homog�nes 4x4 - fa�on GL (2018.12.25)   */
  #include <g3x_quaternions.h>
  #include <g3x_pnm.h>
  #include <g3x_window.h>     /* routines et fonctions de base            */
  
  #endif  

#ifdef __cplusplus
  }
#endif
/*===============================================================*/
