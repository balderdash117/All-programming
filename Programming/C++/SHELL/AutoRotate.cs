using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AutoRotate : MonoBehaviour {

	public float rotSpeed;

	// Update is called once per frame
	void Update () {
		transform.Rotate (new Vector3 (0, rotSpeed * Time.deltaTime, 0));	
	}
}
