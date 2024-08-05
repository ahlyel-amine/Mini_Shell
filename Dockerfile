FROM gcc:10-bookworm

WORKDIR /app

COPY . .

CMD ["bash", "entry.sh"]
