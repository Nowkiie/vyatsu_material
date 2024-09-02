//	 variable arguments macros 


#ifndef	_STDARG

typedef void *	va_list[1];
#define	va_start(ap, parmn)	*ap = (char *)&parmn + sizeof parmn
#define	va_arg(ap, type)	(*(*(type **)ap)++)
#define	_STDARG

#endif	/* STDARG */
