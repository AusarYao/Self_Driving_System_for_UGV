fun main(){
    println("Hello World")
}

//fun pingYourTCPServerWith(message: String): String{
//    try {
//        val socket = Socket("<YOUR IP ADDRESS>", <YOUR PORT HERE>)
//        socket.use {
//
//            var responseString : String? = null
//
//            it.getOutputStream().write(message.toByteArray())
//            val bufferReader = BufferedReader(InputStreamReader(it.inputStream))
//            while (true) {
//                val line = bufferReader.readLine() ?: break
//                responseString += line
//                if (line == "exit") break
//            }
//            println("Received: $responseString")
//            bufferReader.close()
//            it.close()
//            return responseString!!
//        }
//    }catch (he: UnknownHostException){
//        val exceptionString = "An exception occurred:\n ${he.printStackTrace()}"
//        return   exceptionString
//    }catch (ioe: IOException){
//        val exceptionString = "An exception occurred:\n ${ioe.printStackTrace()}"
//        return   exceptionString
//    } catch (ce: ConnectException){
//        val exceptionString = "An exception occurred:\n ${ce.printStackTrace()}"
//        return   exceptionString
//    }catch (se: SocketException){
//        val exceptionString = "An exception occurred:\n ${se.printStackTrace()}"
//        return   exceptionString
//    }
//}