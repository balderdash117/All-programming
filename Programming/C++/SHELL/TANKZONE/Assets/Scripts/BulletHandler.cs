using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class BulletHandler : NetworkBehaviour {

	[SyncVar]
	public NetworkInstanceId owner;

	public GameObject explosionObject;
	public float deadTime, damageRadius;
	public int damageVal; 
	public bool explodeOnImpact, explodeOnTimeout;

	private float _currtime;

	// Use this for initialization
	void Start () {

		GameObject obj = ClientScene.FindLocalObject (owner);
		foreach (Collider col in obj.GetComponentsInChildren<Collider>()) {
			Physics.IgnoreCollision (GetComponent<Collider> (), col);
		}
	}
	
	// Update is called once per frame
	void Update () {

		_currtime += Time.deltaTime;

		if (_currtime < 0) 
		{
			if (explodeOnImpact) 
			{
				CmdExplode (transform.position, Quaternion.identity.eulerAngles);
			}
			NetworkServer.Destroy (gameObject);
		}
	}

	void radiusDamage(Vector3 pos)
	{
		foreach (GameObject obj in GameObject.FindGameObjectsWithTag("Player"))
		{
			if (Vector3.Distance (obj.transform.position, pos) < damageRadius) 
			{
				obj.GetComponent<TankController> ().AdjustCurHealth (-damageVal);
			}
		}
	}

	[ServerCallback]
	void OnCollisionEnter(Collision col)
	{
		if (explodeOnImpact) 
		{			
			CmdExplode (col.contacts [0].point, col.contacts [0].normal);
			NetworkServer.Destroy (gameObject);
		}
	}

	[Command]
	void CmdExplode(Vector3 pos, Vector3 rot)
	{
		GameObject explosion = GameObject.Instantiate (explosionObject, pos, Quaternion.Euler (rot));
		NetworkServer.Spawn (explosion);
	}
}
