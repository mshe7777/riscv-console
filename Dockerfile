FROM cjnitta/riscv_base

<<<<<<< HEAD
# Install packages and add user so that container does not run as root 
RUN apt-get update && apt-get install sudo libgtk-3-dev dbus-x11 -y --no-install-recommends && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/\* /tmp/\* /var/tmp/* && \
    useradd -m docker 
=======
RUN apt-get update && apt-get install sudo libgtk-3-dev dbus-x11 -y

# Add user so that container does not run as root 
RUN useradd -m docker 
>>>>>>> b0044aecb2053ff8d5c73f868ce8aa905487e026

COPY . /code
WORKDIR /code


CMD ["/bin/bash"]
