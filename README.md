# ICDB

ICDB is a column based associative database.

ICDB is built using LSM style structure for each of the columns.

## Query language

At the moment ICDB is just a KV store, but the intention being to work towards a
structured query language tailored for use with ICDB.

In order to simplify the "front-end" of the application we are going to be using a 
styled query language.

```example server configuration
define {
    users : [
        { 
            name: root,
            password: dsafsdsad,    
        },
        {
            name: carl,
            password: adfsdf,
        }
    ],
    
    port : 8000 
}
```

```example database definition
define {
    database {
        name: blog,
        access: [
            {user: carl, scope: [read]},
            {user: root, scope: [read, write]}
        }
    }
    table {
        tables: [
            user : {
                id: int,
                name: string,
                email: string,
                password: string,
                primary: id,
                secondary: [name, email]
            },
            post : {
                id: int,
                title: string,
                content: string,
                author_id: int,
                primary: id,
                references: {author_id: user(id)}
            }
        ]
    }
}
```

And here is an example query

```example queries
get {
    columns: [content]
    location: {
        post : {
            filter: {
                owner: 4;
            }
        }
    }
}

get {
    columns: [t1.content]
    location: {
        user : {
            filter : {
                owner: 4;
            }
            rename: u;
        };
        post : { rename : b};
        flat : {
            merge: [u.id, b.author_id 
        }
    }
}
```