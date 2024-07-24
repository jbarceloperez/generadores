FROM debian:latest
ENV DEBIAN_FRONTEND=noninteractive

# Actualizar e instalar dependencias necesarias
RUN apt-get update && apt-get install -y \
    dbus-tests \
    libdrm2 \
    libegl1 \
    libfontconfig1 \
    libfreetype6 \
    libgl1 \
    libglib2.0-0 \
    libgssapi-krb5-2 \
    libwayland-client0 \
    libwayland-cursor0 \
    libwayland-egl1 \
    libx11-6 \
    libx11-xcb1 \
    libxcb-cursor0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-render0 \
    libxcb-shape0 \
    libxcb-shm0 \
    libxcb-sync1 \
    libxcb-xfixes0 \
    libxcb-xkb1 \
    libxcb1 \
    libxkbcommon-x11-0 \
    libxkbcommon0 \
    python-is-python3 \
    python3 \
    cmake \
    python3-pip \
    python3-venv \
    git \
    zip \
    make \
    qtbase5-dev \
    qttools5-dev-tools \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libgl1-mesa-glx \
    gdb \
    valgrind \
    libdbus-1-3 \
    libxcb-xinerama0 \
    x11-utils \
    x11-apps \
    qtcreator && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Configurar variables de entorno
ENV LC_ALL=C.UTF-8 \
    QTVERSION=6.6.0 \
    DISPLAY=:0

# Instalar herramientas Python y Qt
RUN pip3 install --upgrade pip --break-system-packages && \
    pip3 install aqtinstall --break-system-packages && \
    pip3 install -U gcovr --break-system-packages && \
    aqt install-qt linux desktop $QTVERSION --outputdir /opt/Qt

# Configurar el PATH y las variables de entorno de Qt
ENV PATH="/opt/Qt/6.6.0/gcc_64/bin:${PATH}" \
    QT_QPA_PLATFORM_PLUGIN_PATH=/opt/Qt/6.6.0/gcc_64/plugins/platforms \
    QT_QPA_PLATFORM=xcb

# Copiar y dar permisos al script de ejecución
COPY run.sh /run.sh
RUN chmod +x /run.sh

# Comando por defecto
CMD ["/bin/bash", "/run.sh", "bash"]