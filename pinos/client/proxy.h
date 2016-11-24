/* Pinos
 * Copyright (C) 2015 Wim Taymans <wim.taymans@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef __PINOS_PROXY_H__
#define __PINOS_PROXY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <pinos/client/connection.h>

typedef struct _PinosProxy PinosProxy;

typedef SpaResult (*PinosSendFunc)     (void             *object,
                                        uint32_t          id,
                                        PinosMessageType  type,
                                        void             *message,
                                        bool              flush,
                                        void             *data);

typedef SpaResult (*PinosDispatchFunc) (void             *object,
                                        PinosMessageType  type,
                                        void             *message,
                                        void             *data);
#include <pinos/client/context.h>

struct _PinosProxy {
  PinosContext *context;
  SpaList       link;

  uint32_t      id;
  uint32_t      type;

  PinosSendFunc      send_func;
  void              *send_data;
  PinosDispatchFunc  dispatch_func;
  void              *dispatch_data;

  PINOS_SIGNAL (destroy_signal, (PinosListener *listener,
                                 PinosProxy    *proxy));
};

PinosProxy *      pinos_proxy_new                     (PinosContext      *context,
                                                       uint32_t           id,
                                                       uint32_t           type);
void              pinos_proxy_destroy                 (PinosProxy        *proxy);

SpaResult         pinos_proxy_send_message            (PinosProxy        *proxy,
                                                       PinosMessageType   type,
                                                       void              *message,
                                                       bool               flush);

#ifdef __cplusplus
}
#endif


#endif /* __PINOS_PROXY_H__ */