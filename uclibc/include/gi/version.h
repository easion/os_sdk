


#ifndef __GI_VERSION_H__
#define __GI_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define GIX_MAJOR_VERSION  (1)
#define GIX_MINOR_VERSION  (0)
#define GIX_MICRO_VERSION  (3)

#define GIX_VERSION_CODE(m1,m2,m3) ( (m1) << 16 | (m2) << 8 | (m3) )
#define GIX_CURRENT_VERSION GIX_VERSION_CODE(GIX_MAJOR_VERSION,GIX_MINOR_VERSION,GIX_MICRO_VERSION)

#ifdef __cplusplus
}
#endif
#endif


