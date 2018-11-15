Simple b64_pton() and b64_ntop()
================================

Simple implementation of [Base64](https://www.rfc-editor.org/rfc/rfc4648.txt)
encoding and decoding.  Libc standard doesn't seem to have such
implementations for this moment.

This implementation is to be used by being embedded within programs.
