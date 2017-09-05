using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

[System.Serializable]
public class turret
{
	public Transform horizontalPivot, verticalPivot, gunBarrel, muzzlePt;
	public float pivotSpeed, fireRate, muzzleVelocity;
	public GameObject bullet;
}

public class TankController : NetworkBehaviour 
{
	
	public float moveSpeed, rotSpeed;
	public turret turrets;
	private Camera cam;

	// Use this for initialization
	void Start () 
	{
		cam = transform.FindChild ("Camera").GetComponent<Camera>();
		if (isLocalPlayer) 
		{
			
		} 
		else
		{
			Destroy (cam.gameObject);
		}
	}
	
	// Update is called once per frame
	void Update () 
	{
		if (isLocalPlayer) 
		{
			float y, z;

			y = Input.GetAxis ("Horizontal");
			z = Input.GetAxis ("Vertical");
			//x = Input.GetAxis("Vertical");

			Debug.Log ("Rotation " + y.ToString () + " Forward " + z.ToString ());

			Vector3 moveDir = new Vector3 (0, 0, (moveSpeed * Time.deltaTime) * z);
			transform.Rotate (0, (rotSpeed * Time.deltaTime) * y, 0, Space.Self);

			transform.Translate (moveDir, Space.Self);

			Vector3 aimPos = Vector3.zero;
			Ray ray = cam.ScreenPointToRay (new Vector3 (Input.mousePosition.x, Input.mousePosition.y, 1));
			RaycastHit hit;
			if (Physics.Raycast (ray, out hit, Mathf.Infinity)) {
				aimPos = hit.point;
			} else {
				aimPos = ray.GetPoint (100);
			}

			Quaternion wantedhRot = Quaternion.LookRotation ((aimPos - turrets.horizontalPivot.position).normalized, Vector3.up);

			Quaternion wantedvRot = Quaternion.LookRotation ((aimPos - turrets.verticalPivot.position).normalized, Vector3.up);

			turrets.horizontalPivot.rotation = Quaternion.Euler (new Vector3 (turrets.horizontalPivot.eulerAngles.x,Mathf.LerpAngle(turrets.horizontalPivot.eulerAngles.y,wantedhRot.eulerAngles.y, turrets.pivotSpeed*Time.deltaTime), turrets.horizontalPivot.eulerAngles.z));

			turrets.verticalPivot.rotation = Quaternion.Euler (new Vector3 (Mathf.LerpAngle(turrets.verticalPivot.eulerAngles.x, wantedvRot.eulerAngles.x, turrets.pivotSpeed*Time.deltaTime), turrets.verticalPivot.eulerAngles.y, wantedvRot.eulerAngles.z));

			if (Input.GetMouseButtonDown (0)) 
			{
				CmdSpawnBullet ();
			}
		}
	}
	[Command]
	void CmdSpawnBullet()
	{

			GameObject bullet = GameObject.Instantiate (turrets.bullet, turrets.muzzlePt.position, turrets.muzzlePt.rotation);

			bullet.GetComponent<bulletHnadle> ().owner = netId;
			bullet.GetComponent<Rigidbody> ().AddForce(turrets.muzzlePt.TransformDirection(new Vector3(0,0,turrets.muzzleVelocity)), ForceMode.Impulse);

			NetworkServer.Spawn (bullet);

	}
}
