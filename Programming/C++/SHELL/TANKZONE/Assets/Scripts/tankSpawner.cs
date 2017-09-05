using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class tankSpawner : NetworkBehaviour {

	public GameObject[] tanks = new GameObject []{};
	public Transform[] spawnPoints = new Transform[]{ };
	public int numDeaths;

	private GameObject _curTank;

	// Use this for initialization
	void Start () 
	{
		CmdspawnTank ();
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (_curTank == null) 
		{
			GetComponent<NetworkIdentity> ().localPlayerAuthority = true;
			CmdspawnTank ();
			numDeaths++;
		}
	}

	[Command]
	void CmdspawnTank()
	{
		int r = Random.Range(0, spawnPoints.Length);
		GameObject obj = GameObject.Instantiate (tanks [Random.Range (0, tanks.Length)], spawnPoints [r].position, spawnPoints [r].rotation);

		_curTank = obj;
		NetworkServer.Spawn (obj);
		obj.GetComponent<NetworkIdentity> ().localPlayerAuthority = true;
		GetComponent<NetworkIdentity> ().localPlayerAuthority = false;
	}
}
