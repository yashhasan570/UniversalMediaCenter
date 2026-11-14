package org..eventclient.demo;

import java.io.File;
import java.io.IOException;
import java.net.Inet4Address;
import java.net.InetAddress;

import org..eventclient.Client;

/**
 * Simple Demo EventClient
 * @author Stefan Agner
 *
 */
public class DemoClient1 {

	/**
	 * Simple Demo EventClient
	 * @param args
	 */
	public static void main(String[] args) throws IOException, InterruptedException {
		InetAddress host = Inet4Address.getByAddress(new byte[] { (byte)127, 0, 0, 1 } );

		Thread.sleep(20000);

		String iconFile = "/usr/share//media/icon.png";

		if (! new File(iconFile).exists()) {
			iconFile = "../../icons/icon.png";

			if (! new File(iconFile).exists()) {
				iconFile = "";
			}
		}

		Client oClient = null;

		if (iconFile != "") {
			oClient = new Client(host, 9777, "My Client", iconFile);
		} else {
			oClient = new Client(host, 9777, "My Client");
		}

		Thread.sleep(7000);

		oClient.sendNotification("My Title", "My Message");


		Thread.sleep(7000);

		oClient.sendButton("KB", "escape", false, true, false, (short)0 , (byte)0);


		Thread.sleep(7000);
		oClient.sendButton("KB", "escape", true, true, false, (short)0 , (byte)0);
		oClient.sendNotification("My Title", "Escape sent");

		Thread.sleep(1000);

		oClient.sendButton("KB", "escape", true, false, false, (short)0 , (byte)0);
		oClient.sendNotification("My Title", "Escape released");

		Thread.sleep(7000);
		oClient.sendLog((byte)0, "My Client disconnects....");
		oClient.sendNotification("My Title", "Client will disconnect");
		oClient.stopClient();

	}

}
