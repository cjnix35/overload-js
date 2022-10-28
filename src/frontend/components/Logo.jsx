const Logo = () => {
  return (
    <svg
      className="animate-pulse"
      width="296"
      height="296"
      viewBox="0 0 296 296"
      fill="none"
      xlmns="http://www.w3.org/2000/svg"
    >
      <g id="polygon_overload">
        <path
          id="polygon"
          d="M143.802 2.3094C146.277 0.880339 149.326 0.880339 151.802 2.3094L271.802 71.5914C274.277 73.0205 275.802 75.6615 275.802 78.5196V217.084C275.802 219.942 274.277 222.583 271.802 224.012L151.802 293.294C149.326 294.723 146.277 294.723 143.802 293.294L23.8017 224.012C21.3265 222.583 19.8017 219.942 19.8017 217.084V78.5196C19.8017 75.6615 21.3265 73.0205 23.8017 71.5914L143.802 2.3094Z"
          fill="url(#paint0_linear_152_4932)"
        />

        <g id="arrows" className="animate-arrows_animation">
          <path
            id="right"
            d="M200.764 207.195L240.752 147.597L200.764 88H166.852L204.994 147.597L166.852 207.195H200.764Z"
            fill="white"
          />
          <path
            id="center"
            d="M144.742 207.195L184.731 147.597L144.742 88H110.83L148.972 147.597L110.83 207.195H144.742Z"
            fill="white"
          />
          <path
            id="left"
            d="M89.9121 207.195L129.901 147.597L89.9121 88H56L94.1424 147.597L56 207.195H89.9121Z"
            fill="white"
          />
        </g>
      </g>
      <defs>
        <linearGradient
          id="paint0_linear_152_4932"
          x1="222.968"
          y1="48.6444"
          x2="60.2077"
          y2="293.292"
          gradientUnits="userSpaceOnUse"
        >
          <stop stopColor="#F73221" />
          <stop offset="1" stopColor="#F73221" stopOpacity={0.4} />
          <stop offset="1" stopColor="#F73221" stopOpacity={0.4} />
        </linearGradient>
      </defs>
    </svg>
  );
};

export default Logo;
