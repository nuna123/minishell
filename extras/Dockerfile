FROM debian:latest

# Install necessary dependencies
RUN apt-get update -y && apt-get install -y \
    git \
    build-essential \
    libreadline-dev \
    make

# Set working directory
WORKDIR /app

# Copy the minishell folder into the container during build
COPY ./minishell ./minishell

# Build the project
RUN make -C minishell

# Set the default command to run minishell
CMD ["./minishell/minishell"]
