/*
 * Copyright (C) 2006-2007, 2009 Red Hat, Inc.
 *
 * Author: Steven Dake <sdake@redhat.com>
 *
 * This file is part of libqb.
 *
 * libqb is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * libqb is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libqb.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef QB_IPCC_H_DEFINED
#define QB_IPCC_H_DEFINED

/* *INDENT-OFF* */
#ifdef __cplusplus
extern "C" {
#endif
/* *INDENT-ON* */

#include <qb/qbconfig.h>

#include <pthread.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <qb/qbhdb.h>
#include <qb/qbipc_common.h>

/**
 * @file qbipcc.h
 *
 * Client IPC API.
 *
 * @par Lifecycle of an IPC connection.
 * An IPC connection is made to the server with qb_ipcc_connect(). This function
 * connects to the server and requests channels be created for communication.
 * To disconnect, the client either exits or executes the function qb_ipcc_disconnect().
 *
 * @par Synchronous communication
 * The function qb_ipcc_sendv_recv() sends an iovector request and receives a response.
 *
 * @par Asynchronous requests from the client
 * The function qb_ipcc_sendv() sends an iovector request.
 * The function qb_ipcc_send() sends an message buffer request.
 *
 * @par Asynchronous events from the server
 * The qb_ipcc_event_recv() function receives an out-of-band asyncronous message.
 * The asynchronous messages are queued and can provide very high out-of-band performance.
 * To determine when to call qb_ipcc_event_recv() the qb_ipcc_fd_get() call is
 * used to obtain a file descriptor used in the poll() or select() system calls.
 *
 * @example ipcclient.c
 * This is an example of how to use the client.
 */

typedef struct qb_ipcc_connection qb_ipcc_connection_t;

/**
 * Create a connection to an IPC service.
 *
 * @param name name of the service.
 * @param max_msg_size biggest msg size.
 * @return NULL (error: see errno) or a connection object.
 */
qb_ipcc_connection_t*
qb_ipcc_connect(const char *name, size_t max_msg_size);

/**
 * Disconnect an IPC connection.
 *
 * @param c connection instance
 */
void qb_ipcc_disconnect(qb_ipcc_connection_t* c);

/**
 * Get the file descriptor to poll.
 *
 * @param c connection instance
 * @param fd (out) file descriptor to poll
 */
int32_t qb_ipcc_fd_get(qb_ipcc_connection_t* c, int32_t * fd);

/**
 * Set the maximum allowable flowcontrol value.
 *
 * @note the default is 1
 *
 * @param c connection instance
 * @param max the max allowable flowcontrol value (1 or 2)
 */
int32_t qb_ipcc_fc_enable_max_set(qb_ipcc_connection_t * c, uint32_t max);

/**
 * Send a message.
 *
 * @param c connection instance
 * @param msg_ptr pointer to a message to send
 * @param msg_len the size of the message
 * @return (size sent, -errno == error)
 */
ssize_t qb_ipcc_send(qb_ipcc_connection_t* c, const void *msg_ptr,
                     size_t msg_len);
/**
 * Send a message (iovec).
 *
 * @param c connection instance
 * @param iov pointer to an iovec struct to send
 * @param iov_len the number of iovecs used
 * @return (size sent, -errno == error)
 */
ssize_t qb_ipcc_sendv(qb_ipcc_connection_t* c, const struct iovec* iov,
	size_t iov_len);
/**
 * Receive a response.
 *
 * @param c connection instance
 * @param msg_ptr pointer to a message buffer to receive into
 * @param msg_len the size of the buffer
 * @param ms_timeout max time to wait for a response
 * @return (size recv'ed, -errno == error)
 */
ssize_t qb_ipcc_recv(qb_ipcc_connection_t* c, void *msg_ptr,
                     size_t msg_len, int32_t ms_timeout);

/**
 * This is a convenience function that simply sends and then recvs.
 *
 * @param c connection instance
 * @param iov pointer to an iovec struct to send
 * @param iov_len the number of iovecs used
 * @param msg_ptr pointer to a message buffer to receive into
 * @param msg_len the size of the buffer
 * @param ms_timeout max time to wait for a response
 *
 * @see qb_ipcc_sendv() qb_ipcc_recv()
 */
ssize_t qb_ipcc_sendv_recv(qb_ipcc_connection_t *c,
			   const struct iovec *iov, uint32_t iov_len,
			   void *msg_ptr, size_t msg_len,
			   int32_t ms_timeout);

/**
 * Receive an event.
 *
 * @param c connection instance
 * @param msg_ptr pointer to a message buffer to receive into
 * @param msg_len the size of the buffer
 * @param ms_timeout time in milli seconds to wait for a message
 *        0 == no wait, negative == block, positive == wait X ms.
 * @param ms_timeout max time to wait for a response
 * @return size of the message or error (-errno)
 */
ssize_t qb_ipcc_event_recv(qb_ipcc_connection_t* c, void *msg_ptr,
			   size_t msg_len, int32_t ms_timeout);

/**
 * Associate a "user" pointer with this connection.
 *
 * @param context the point to associate with this connection.
 * @param c connection instance
 * @see qb_ipcc_context_get()
 */
void qb_ipcc_context_set(qb_ipcc_connection_t *c, void *context);

/**
 * Get the context (set previously)
 *
 * @param c connection instance
 * @return the context
 * @see qb_ipcc_context_set()
 */
void *qb_ipcc_context_get(qb_ipcc_connection_t *c);


/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

#endif /* QB_IPCC_H_DEFINED */
