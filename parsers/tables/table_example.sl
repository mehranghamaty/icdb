
user {
    id: int,
    name: string,
    password: string,
}

post {
    id: int,
    content: string,
    owner: int references user
}

