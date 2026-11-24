#ifndef SESSION_H
#define SESSION_H
/*
 * session_create - Creates a session and takes ownership of username.
 * @username: Dynamically allocated username transferred to the session.
 *
 * Return: Pointer to the new session, or NULL on failure.
 */
typedef struct session
{
    char *user;
    int access_level;
} session_t;

session_t *session_create(char *username);
void session_print(session_t *session);
void session_destroy(session_t *session);

#endif
