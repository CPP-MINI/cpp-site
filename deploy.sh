#!/bin/bash
USER=cpp
HOST=ssh.mini.pw.edu.pl
DIR=public_html

hugo && rsync -avz --delete public/ ${USER}@${HOST}:~/${DIR}
