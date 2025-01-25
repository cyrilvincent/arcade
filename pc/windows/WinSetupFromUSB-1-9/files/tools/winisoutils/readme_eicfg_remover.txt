ei.cfg Removal Utility
Version 1.2.1
<http://code.kliu.org/misc/winisoutils/>

When used on an original Windows 7/8 ISO image, this utility will disable the
ei.cfg file, thus converting a disc image into a "universal" disc image.

When used on a Windows 7/8 ISO image that has already been patched by this
utility, this utility will undo the ei.cfg removal and restore the disc image
to its original state.


Troubleshooting
===============

The inability to open the disc image with write access is, by far, the most
common error.  Make sure that the disc image is not read-only, that you have
write privileges for the disc image, and that the disc image is not open in or
currently in use by another application.


Technical Details
=================

This works by toggling the deletion bit in the UDF file table, which instructs
the operating system to ignore the file and to treat it as if it does not exist.
By not physically removing the file, this eliminates the need to rebuild the
ISO, and makes this sort of fast, unintrustive patching possible.  This also
makes it possible to reverse the patch and to restore the image to its original
state, if so desired.


Changelog
=========

2012/08/06 - 1.2.1
	The search for ei.cfg is now case-insensitive.

2011/01/25 - 1.2
	Made the error messages more helpful.

2009/08/10 - 1.1
	Changed the patching methodology to use the UDF deletion bit instead of
	renaming the file.

2009/08/10 - 1.0
	Initial version.


Version Compatibility Note
==========================

ei.cfg Removal Utility versions 1.1 and later use a slightly different patching
method than version 1.0, and as a result, the newer versions cannot reverse the
patches performed by version 1.0, and vice-versa; to reverse a patch that was
performed by version 1.0, you must use version 1.0.

Since version 1.0 existed for only 8 hours before being replaced by version 1.1,
this should not be a problem for most users.
