using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

[System.Serializable]
public class Turret
{
	public Transform horizontalPivot, verticalPivot, gunBarrel, muzzlePoint;
	public float pivotSpeed, firingRate, muzzleVelocity, currCooldown;
	public GameObject bullet;
}


public class TankController :  NetworkBehaviour{

	public float 		moveSpeed, rotationSpeed;
	private int			_currHealth, _maxHealth;
	public Turret[] 	turrets = new Turret[]{};
	private bool 		_isFiring;

	private Camera 		_cam;

	// Use this for initialization
	void Start () {
		_cam = transform.FindChild ("Camera").GetComponent<Camera> ();
		if (isLocalPlayer) {

		} else
			Destroy(_cam.gameObject);
	}
	
	// Update is called once per frame
	void Update () {
		if (isLocalPlayer) {

			// Check keypresses
			if (Input.GetAxisRaw ("Fire1") == 1) {				// Normalize axis (on|off)
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

			// Update rotation
			foreach (Turret turret in turrets) {
				if (turret.currCooldown >= 0) {
					turret.currCooldown -= Time.deltaTime;
				}

				Quaternion wantedHRot = Quaternion.LookRotation (
					                       (aimPos - turret.horizontalPivot.position).normalized, Vector3.up);
				Quaternion wantedVRot = Quaternion.LookRotation (
					                       (aimPos - turret.verticalPivot.position).normalized, Vector3.up);
		
				turret.horizontalPivot.rotation = Quaternion.Euler (
					new Vector3 (turret.horizontalPivot.eulerAngles.x,
					/*Current rotation, intended rotation, velocity*/
						Mathf.LerpAngle (turret.horizontalPivot.eulerAngles.y, wantedHRot.eulerAngles.y, turret.pivotSpeed * Time.deltaTime),			// Add friction to turret movement														
						turret.horizontalPivot.eulerAngles.z));

				turret.verticalPivot.rotation = Quaternion.Euler (
					new Vector3 (Mathf.LerpAngle (turret.verticalPivot.eulerAngles.x, wantedVRot.eulerAngles.x, turret.pivotSpeed * Time.deltaTime), 
						turret.verticalPivot.eulerAngles.y,
						turret.verticalPivot.eulerAngles.z));

				if (_isFiring && turret.currCooldown < 0) {
					CmdSpawnBullet (turret);
					turret.currCooldown = turret.firingRate;
				}

			}
		}
	}
	public void AdjustCurrentHealth(int val) {
		_currHealth += val;

		if (_currHealth <= 0) {
			NetworkServer.Destroy (gameObject);
		}
	}
	[Command]
	void CmdSpawnBullet(Turret turret)
	{
		GameObject bullet = GameObject.Instantiate (turret.bullet, 
			turret.muzzlePoint.position, 
			turret.muzzlePoint.rotation);

		bullet.GetComponent<BulletHandler> ().owner = netId;
		bullet.GetComponent<Rigidbody> ().AddForce(turret.muzzlePoint.TransformDirection(
			new Vector3(0,0,turret.muzzleVelocity)), ForceMode.Impulse);
		NetworkServer.Spawn (bullet);
	}
}
