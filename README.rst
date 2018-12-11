myhttpserver
============

Description
-----------

This is just a small multithreaded http server to learn C and system programmation. It needs a script to actually build the http responses (see ``example/example.py``)

Installation
------------

1) Clone the repository

2) Make it your working directory

3) Build the application

.. code-block:: bash

   make

How to use it
-------------

Run

.. code-block:: bash

   ./myhttpserver [-p portNo] [cmd]

where:

- ``portNo`` is the TCP port where the server listens for a new connection

- ``cmd`` is the actual command to launch the process in charge of building the http response.

``cmd`` must be an installed binary so that ``/usr/bin/env cmd`` will launch it, with potential additional parameters

You can get help with ``./myhttpserver -h``

Ideas for improvements
----------------------

- So far the server only works with request smaller than 1024 bytes, and sends only responses up to 1024 bytes: it could be interesting to make it work by chunks so it can serve larger requests and responses
- Keep sockets alive for requests coming from same clients
- Test suite
