#ifndef BASEANIMATION_H
#define BASEANIMATION_H

#include <core/Resource.h>
#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/matrix_operation.hpp>
#include <glm/gtx/transform.hpp>

class BaseAnimation: public Resource {
public:
	BaseAnimation();
	~BaseAnimation();

	// The JointInfo stores the information necessary to build the
	// skeletons for each frame
	struct JointInfo
	{
		std::string m_Name;
		int         m_ParentID;
		int         m_Flags;
		int         m_StartIndex;
	};
	typedef std::vector<JointInfo> JointInfoList;

	struct Bound
	{
		glm::vec3   m_Min;
		glm::vec3   m_Max;
	};
	typedef std::vector<Bound> BoundList;

	struct BaseFrame
	{
		glm::vec3   m_Pos;
		glm::quat   m_Orient;
	};
	typedef std::vector<BaseFrame> BaseFrameList;

	struct FrameData
	{
		int m_iFrameID;
		std::vector<float> m_FrameData;
	};
	typedef std::vector<FrameData> FrameDataList;

	// A Skeleton joint is a joint of the skeleton per frame
	struct SkeletonJoint
	{
		SkeletonJoint()
			: m_Parent(-1)
			, m_Pos(0)
		{}

		SkeletonJoint(const BaseFrame& copy)
			: m_Pos(copy.m_Pos)
			, m_Orient(copy.m_Orient)
		{}

		int         m_Parent;
		glm::vec3   m_Pos;
		glm::quat   m_Orient;
	};
	typedef std::vector<SkeletonJoint> SkeletonJointList;

	// A frame skeleton stores the joints of the skeleton for a single frame.
	struct FrameSkeleton
	{
		SkeletonJointList   m_Joints;
	};
	typedef std::vector<FrameSkeleton> FrameSkeletonList;


	JointInfoList       m_JointInfos;
	BoundList           m_Bounds;
	BaseFrameList       m_BaseFrames;
	FrameDataList       m_Frames;
	FrameSkeletonList   m_Skeletons;    // All the skeletons for all the frames

	FrameSkeleton       m_AnimatedSkeleton;

protected:
	int m_iMD5Version;
	int m_iNumFrames;
	int m_iNumJoints;
	int m_iFramRate;
	int m_iNumAnimatedComponents;

	float m_fAnimDuration;
	float m_fFrameDuration;
	float m_fAnimTime;
};
#endif
