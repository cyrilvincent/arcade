cversion.ini Removal Utility
Version 1.0.0
<http://code.kliu.org/misc/winisoutils/>

When used on a Windows ISO image, this utility will disable the cversion.ini
file; this will remove the restrictions preventing you from performing an
in-place upgrade of Windows 8 RP to Windows 8 RTM or Windows 8.1 Preview to
Windows 8.1 RTM, allowing you to keep all user data intact through the upgrade.

When used on a Windows ISO image that has already been patched by this utility,
this utility will undo the cversion.ini removal and restore the disc image to
its original state.


WARNING
=======

These sorts of upgrades were purposefully disabled by Microsoft and are thus
UNSUPPORTED. Although many users have reported success with such in-place
upgrades, the lack of official support means that there is no guarantee that
they will be problem-free. If you are uncomfortable with this, you should
perform a clean install instead.


Troubleshooting
===============

The inability to open the disc image with write access is, by far, the most
common error. Make sure that the disc image is not read-only, that you have
write privileges for the disc image, and that the disc image is not open in or
currently in use by another application.


Technical Details
=================

This works by toggling the deletion bit in the UDF file table, which instructs
the operating system to ignore the file and to treat it as if it does not exist.
By not physically removing the file, this eliminates the need to rebuild the
ISO, and makes this sort of fast, unintrustive patching possible. This also
makes it possible to easily reverse the patch and to restore the image to its
original state, if so desired.


Changelog
=========

2013/08/31 - 1.0
	Initial version.
