using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class BulletHandler : NetworkBehaviour {

	[SyncVar]
	public NetworkInstanceId owner;

	public GameObject explosionObject;
	public float deadTime;
	//ADD DAMAGE
	public int 		damageVal;
	public bool 	explodeOnImpact, explodeOnTimeout;

	// Use this for initialization
	void Start () {

		GameObject obj = ClientScene.FindLocalObject (owner);
		foreach (Collider col in obj.GetComponentsInChildren<Collider>()) {
			Physics.IgnoreCollision (GetComponent<Collider> (), col);
		}
	}
	
	// Update is called once per frame
	void Update () {


	}

	[ServerCallback]
	void OnCollisionEnter(Collision col)
	{
		if (col.gameObject.layer == 8) {
			col.transform.root.GetComponent<TankController> ().AdjustCurrentHealth (-damageVal);
		}

		if (explodeOnImpact) {
			CmdExplode (col.contacts [0].point, col.contacts [0].normal);
		}
	}

	[Command]
	void CmdExplode(Vector3 pos, Vector3 rot)
	{
		GameObject explosion = GameObject.Instantiate (explosionObject, pos, Quaternion.Euler (rot));
		NetworkServer.Spawn (explosion);
	}
}
