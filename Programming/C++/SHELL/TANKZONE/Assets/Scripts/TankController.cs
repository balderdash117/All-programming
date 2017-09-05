using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

[System.Serializable]
public class Turret
{
	public Transform horizontalPivot, verticalPivot, gunBarrel, muzzlePoint;
	public float pivotSpeed, firingRate, muzzleVelocity, curCooldown;
	public string bulletName;
}
	
public class TankController :  NetworkBehaviour {

	public float moveSpeed, rotationSpeed;
	public Turret[] turrets = new Turret[]{};
	public int maxHealth;

	private int _curHealth;
	private bool _isFiring;
	private Camera _cam;



	// Use this for initialization
	void Start () {
		name = netId.ToString();
		_curHealth = maxHealth;
		_cam = transform.FindChild ("CamMount").GetChild(0).GetComponent<Camera>();
		if (isLocalPlayer) {
			_cam.transform.parent.GetComponent<CamHandler> ().followObj = transform;
			_cam.transform.parent.parent = null;
		} else
			Destroy(_cam.gameObject);
	}
	

	void Update () {
		if (!isLocalPlayer) {
			return;

		}
		else {
			if (Input.GetAxisRaw ("Fire1") == 1) {
				_isFiring = true;
			} else {
				_isFiring = false;
			}

			float _y, _z;
			_y = Input.GetAxis ("Horizontal");
			_z = Input.GetAxis ("Vertical");

			Vector3 _moveDir = new Vector3 (0, 0, (moveSpeed * Time.deltaTime) * _z);

			transform.Rotate (0, (rotationSpeed * Time.deltaTime) * _y, 0, Space.Self);
			transform.Translate (_moveDir, Space.Self);

			Vector3 aimPos = Vector3.zero;
			Ray ray = _cam.ScreenPointToRay (new Vector3 (Input.mousePosition.x, Input.mousePosition.y, 1));
			RaycastHit hit;
			if (Physics.Raycast (ray, out hit, Mathf.Infinity)) {
				aimPos = hit.point;
			} else {
				aimPos = ray.GetPoint (100);
			}

			foreach (Turret turret in turrets) {

				if (turret.curCooldown >= 0)
					turret.curCooldown -= Time.deltaTime;

				Quaternion wantedHRot = Quaternion.LookRotation (
					                        (aimPos - turret.horizontalPivot.position).normalized, Vector3.up);
				Quaternion wantedVRot = Quaternion.LookRotation (
					                        (aimPos - turret.verticalPivot.position).normalized, Vector3.up);
		
				turret.horizontalPivot.rotation = Quaternion.Euler (
					new Vector3 (turret.horizontalPivot.eulerAngles.x,
						Mathf.LerpAngle (turret.horizontalPivot.eulerAngles.y, wantedHRot.eulerAngles.y, turret.pivotSpeed * Time.deltaTime),
						turret.horizontalPivot.eulerAngles.z));

				turret.verticalPivot.rotation = Quaternion.Euler (
					new Vector3 (Mathf.LerpAngle (turret.verticalPivot.eulerAngles.x, wantedVRot.eulerAngles.x, turret.pivotSpeed * Time.deltaTime),
						turret.verticalPivot.eulerAngles.y,
						turret.verticalPivot.eulerAngles.z));

				if (_isFiring && turret.curCooldown < 0) {
					CreateBullet (turret);
					Debug.Log ("FIRING");
					turret.curCooldown = turret.firingRate;
				}
			}
		}
			
	}
		

	//[ServerCallback]
	public void CreateBullet(Turret turret)
	{
		
		CmdSpawnBullet (turret.bulletName, turret.muzzlePoint.position, turret.muzzlePoint.rotation, turret.muzzlePoint.forward, turret.muzzleVelocity, netId);
	}


	public void AdjustCurHealth(int val)
	{
		_curHealth += val;

		if (_curHealth <= 0)
			NetworkServer.Destroy (gameObject);
	}

	[Command]
	void CmdSpawnBullet(string bulletName, Vector3 muzzlePos, Quaternion muzzleRot, Vector3 muzzleVec, float muzzleVel, NetworkInstanceId id)
	{
		
		GameObject bullet = GameObject.Instantiate ((GameObject)Resources.Load(bulletName), 
			muzzlePos, 
			muzzleRot);

		bullet.GetComponent<BulletHandler> ().owner = netId;
		bullet.GetComponent<Rigidbody> ().AddForce(muzzleVec*muzzleVel, ForceMode.Impulse);
		NetworkServer.Spawn (bullet);
	}
}
