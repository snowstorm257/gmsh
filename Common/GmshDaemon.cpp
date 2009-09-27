// Gmsh - Copyright (C) 1997-2009 C. Geuzaine, J.-F. Remacle
//
// See the LICENSE.txt file for license information. Please report all
// bugs and problems to <gmsh@geuz.org>.

#include <sstream>
#include "GmshMessage.h"
#include "OS.h"
#include "GmshSocket.h"
#include "PView.h"
#include "PViewOptions.h"
#include "PViewData.h"
#include "VertexArray.h"

static void computeAndSendVertexArrays(GmshClient &client)
{
  for(unsigned int i = 0; i < PView::list.size(); i++){
    PView *p = PView::list[i];
    p->fillVertexArrays();
    PViewData *data = p->getData();
    VertexArray *va[4] = 
      {p->va_points, p->va_lines, p->va_triangles, p->va_vectors};
    for(int type = 0; type < 4; type++){
      if(va[type] && va[type]->getNumVertices()){
        int len;
        char *str = va[type]->toChar
          (p->getNum(), type + 1, data->getMin(), data->getMax(),
           data->getTime(0), data->getBoundingBox(), len);
        client.SendMessage(GmshSocket::GMSH_VERTEX_ARRAY, len, str);
        delete [] str;
      }
    }
  }
}

int GmshDaemon(std::string socket)
{
  GmshClient client;

  if(client.Connect(socket.c_str()) < 0){
    Msg::Error("Unable to connect to server on %s", socket.c_str());
    return 1;
  }
  client.Start();
  client.Info("Server sucessfully started. Listening...");

  computeAndSendVertexArrays(client);

  while(1){
    // stop the server if we have no communications for 60 seconds
    int ret = client.Select(60, 0);
    if(!ret){
      client.Info("Timout: stopping server...");
      break;
    }
    else if(ret < 0){
      client.Error("Error on select: stopping server...");
      break;
    }

    int type, length;
    if(!client.ReceiveHeader(&type, &length)){
      client.Error("Did not receive message header: stopping server...");
      break;
    }
      
    char *msg = new char[length + 1];
    if(!client.ReceiveString(length, msg)){
      client.Error("Did not receive message body: stopping server...");
      delete [] msg;
      break;
    }

    if(type == GmshSocket::GMSH_STOP){
      client.Info("Stopping server");
      break;
    }
    else if(type == GmshSocket::GMSH_VERTEX_ARRAY){
      client.Info("Sending vertex arrays");
      computeAndSendVertexArrays(client);
    }
    else if(type == GmshSocket::GMSH_SPEED_TEST){
      client.Info("Sending huge array");
      std::string huge(500000000, 'a');
      client.SpeedTest(huge.c_str());
    }
    else{
      client.Error("Ignoring unknown message");
    }
  }

  client.Stop();
  client.Disconnect();

  return 0;
}
