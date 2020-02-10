import React from 'react';
const PORT = 9000;
// var WebSocketServer = require('websocket').server;
// var http = require('http');

class App extends React.Component {
  constructor(props){
    super(props);
    // this.server = http.createServer(function(request, response) {
      // console.log((new Date()) + ' Received request for ' + request.url);
      // response.writeHead(404);
      // response.end();
  // });
  }

  sendButtonHandler() {
  }

  render()
  {
    return (
      <div className="App">
        <header className="App-header">
          <button onClick={this.sendButtonHandler}>Start Connection</button>
        </header>
      </div>
    );
  }
}

export default App;
