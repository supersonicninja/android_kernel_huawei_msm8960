/// Use kmemdup rather than duplicating its implementation
///
// Confidence: High
<<<<<<< HEAD
// Copyright: (C) 2010 Nicolas Palix, DIKU.  GPLv2.
// Copyright: (C) 2010 Julia Lawall, DIKU.  GPLv2.
// Copyright: (C) 2010 Gilles Muller, INRIA/LiP6.  GPLv2.
=======
// Copyright: (C) 2010-2012 Nicolas Palix.  GPLv2.
// Copyright: (C) 2010-2012 Julia Lawall, INRIA/LIP6.  GPLv2.
// Copyright: (C) 2010-2012 Gilles Muller, INRIA/LiP6.  GPLv2.
>>>>>>> cm-10.0
// URL: http://coccinelle.lip6.fr/
// Comments:
// Options: -no_includes -include_headers

virtual patch
<<<<<<< HEAD
=======
virtual context
virtual org
virtual report
>>>>>>> cm-10.0

@r1@
expression from,to;
expression flag;
position p;
@@

   to = \(kmalloc@p\|kzalloc@p\)(strlen(from) + 1,flag);

@r2@
expression x,from,to;
expression flag,E1;
position p;
@@

    x = strlen(from) + 1;
    ... when != \( x = E1 \| from = E1 \)
    to = \(kmalloc@p\|kzalloc@p\)(x,flag);

<<<<<<< HEAD
@@
=======
@depends on patch@
>>>>>>> cm-10.0
expression from,to,size,flag;
position p != {r1.p,r2.p};
statement S;
@@

-  to = \(kmalloc@p\|kzalloc@p\)(size,flag);
+  to = kmemdup(from,size,flag);
   if (to==NULL || ...) S
-  memcpy(to, from, size);
<<<<<<< HEAD
=======

@r depends on !patch@
expression from,to,size,flag;
position p != {r1.p,r2.p};
statement S;
@@

*  to = \(kmalloc@p\|kzalloc@p\)(size,flag);
   to = kmemdup(from,size,flag);
   if (to==NULL || ...) S
*  memcpy(to, from, size);

@script:python depends on org@
p << r.p;
@@

coccilib.org.print_todo(p[0], "WARNING opportunity for kmemdep")

@script:python depends on report@
p << r.p;
@@

coccilib.report.print_report(p[0], "WARNING opportunity for kmemdep")
>>>>>>> cm-10.0
