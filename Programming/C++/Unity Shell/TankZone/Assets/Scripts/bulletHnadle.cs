using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class bulletHnadle : NetworkBehaviour {

	[SyncVar]
	public NetworkInstanceId owner;

	public GameObject explosionObject;
	public float deadTime;
	public bool explodeOnImpact, explosedOnTimeOut;

	// Use this for initialization
	void Start () 
	{
		GameObject obj = ClientScene.FindLocalObject (owner);

		foreach (Collider col in obj.GetComponentsInChildren<Collider>())
			Physics.IgnoreCollision (GetComponent<Collider> (), col);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
	[ServerCallback]
	void OnCollisonEnter(Collision col)
	{
		if (explodeOnImpact) 
		{
			Cmdexplode (col.contacts [0].point, col.contacts [0].normal);
		}
	}

	[Command]
	void Cmdexplode (Vector3 pos, Vector3 rot)
	{
		GameObject explosion = GameObject.Instantiate (explosionObject, pos, Quaternion.Euler(rot));
		NetworkServer.Spawn (explosion);
	}
}
